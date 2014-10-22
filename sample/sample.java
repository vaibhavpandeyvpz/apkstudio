/*
The MIT License (MIT)

Copyright (c) 2014 Vaibhav Pandey

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */

package com.vaibhavpandey.cli;

import java.io.BufferedWriter;

import android.os.Handler;

public final class Shell implements Closeable {
	public static interface IShell {
        abstract public void onShellClosed();
    }
	private final List<Command> commands;
	private boolean finish;
	private Handler handler;
	private IShell listener;
	private final Process process;
	private final LineNumberReader reader;
	private final BufferedWriter writer;
	private static String TOKEN = "--vpz--";
    /**
     * Starts the generic bash shell (/system/bin/sh)
     *
     * @return  Interactive shell object
     * @throws    IOException if unable to execute shell binary
     */
	public static Shell start() throws IOException {
        return start(false);
    }
    /**
     * Starts the superuser shell (/system/(bin|xbin)/su) or generic bash shell (/system/bin/sh)
     *
     * @param	passing true will start the superuser shell, otherwise bash
     * @return  Interactive shell object
     * @throws    IOException if unable to execute shell binary
     */
	public static Shell start(final boolean root) throws IOException {
        return start(root ? "su" : "sh");
    }
    /**
     * Starts the shell from binary name or absolute path
     *
     * @param    Binary name or path e.g., sh, su or /system/bin/sh
     * @return  Interactive shell object
     * @throws    IOException if unable to execute shell binary
     */
	public static Shell start(String binary) throws IOException {
        File executable = new File(binary);
        if (executable.exists() && executable.isFile() && executable.isAbsolute())
            return new Shell(executable.getAbsolutePath());
        else
            return new Shell(getBinaryPath(binary));
    }
	private Shell(String binary) throws IOException {
        this.commands = new ArrayList<Command>();
        this.finish = false;
        this.handler = new Handler();
    	processBuilder builder = new ProcessBuilder(binary);
        builder.redirectErrorStream(true);
        this.process = builder.start();
        this.reader = new LineNumberReader(new InputStreamReader(this.process.getInputStream()));
        this.writer = new BufferedWriter(new OutputStreamWriter(this.process.getOutputStream()));
        this.bind();
    }
    /**
     * Add a Command to the internal shell execution queue
     *
     * @param    Command object to be added to execution queue
     * @return  Original command object, with shell & ID set
     * @see        Command
     */
	public Command add(Command command) {
        if (this.finish)
            return null;
        synchronized (this.commands) {
            command.setId(this.commands.size());
            this.commands.add(command);
            this.commands.notifyAll();
        }
        return command;
    }
	private void bind() {
        new Thread(new Runnable() {
        	public void run() {
                try {
                    Shell.this.write();
                } catch (IOException e) {
                }
            }
        } , ":input").start();
        new Thread(new Runnable() {
        	public void run() {
                try {
                    Shell.this.read();
                } catch (IOException e) {
                } catch (InterruptedException e) {
                }
            }
        }, ":output").start();
    }
    /**
     * Attempts to close the safely using exit command
     */
	public void close() throws IOException {
        synchronized (this.commands) {
            this.finish = true;
            this.commands.notifyAll();
        }
    }
    /**
     * Attempts to destroy the internal shell process (if running)
     * 
     * @return	process' exit code
     */
	public int destroy() {
        if (!this.isRunning())
            return -1;
        try {
            this.process.destroy();
            return this.process.exitValue();
        } catch (IllegalThreadStateException exception) {
            exception.printStackTrace();
            return -1;
        }
    }
    /**
     * Searches for absolute path to binary name provided
     * 
     * @param    Name of the binary to look for
     * @return    Absolute file path of the found executable
     */
	public static String getBinaryPath(String binary) {
        String[] locations = {
            "/system/bin/",
            "/system/xbin/"
        };
        for (String location : locations) {
            File executable = new File(location + binary);
            if (!executable.exists() || !executable.isFile())
                continue;
            binary = executable.getAbsolutePath();
            break;
        }
        return binary;
    }
    /**
     * Verifies if root access is given to current shell or not
     * 
     * @return    true if uid is set to 0, otherwise false
     */
	public boolean isRoot() {
        final AtomicBoolean root = new AtomicBoolean(false);
        Command command = new Command("id") {
            @Override public void onFinish(int code) { }
            @Override public final void onOutput(int line, String text) {
                if (text.contains("uid=0"))
                    root.set(true);
            }
            @Override public void onStart() { }
        };
        try {
            this.add(command).await();
        } catch (Exception exception) {
            exception.printStackTrace();
        }
        return root.get();
    }
    /**
     * Checks if process is running by querying for exit code
     * 
     * @return    false if able to get exit code, otherwise true
     */
	public boolean isRunning() {
        if (this.process == null)
            return false;
        try {
            this.process.exitValue();
            return false;
        } catch (IllegalThreadStateException exception) {
            exception.printStackTrace();
            return true;
        }
    }
	private void read() throws IOException, InterruptedException {
        Command command = null;
        int current = 0;
        while (true) {
            String line = this.reader.readLine();
            if (line == null)
                break;
            if (command == null) {
                if (current >= this.commands.size()) {
                    if (this.finish)
                        break;
                    continue;
                }
                command = this.commands.get(current);
            }
            int position = line.indexOf(TOKEN);
            if (position > 0)
                command.output(this.reader.getLineNumber(), line.substring(0, position));
            if (position >= 0) {
                line = line.substring(position);
                String segments[] = line.split("\\s");
                if (Integer.parseInt(segments[1]) == current) {
                    this.reader.setLineNumber(0);
                    command.finished(Integer.parseInt(segments[2]));
                    command = null;
                    current++;
                    continue;
                }
            }
            command.output(this.reader.getLineNumber(), line);
        }
        this.process.waitFor();
        this.destroy();
        while (current < this.commands.size()) {
            if (command == null)
                command = this.commands.get(current);
            command.finished(-1);
            command = null;
            current++;
        }
        if (this.listener != null) {
            this.handler.post(new Runnable() {
                @Override public void run() {
                    Shell.this.listener.onShellClosed();
                }
            });
        }
    }
    /**
     * Assign a listener (Shell.IShell) to the shell to receive shell callbacks
     * 
     * @see Shell.IShell
     */
	public void setShellListener(IShell listener) {
        this.listener = listener;
    }
	private void write() throws IOException {
        try {
            int current = 0;
            while (true) {
                synchronized (this.commands) {
                    while (!this.finish && (current >= this.commands.size()))
                        this.commands.wait();
                }
                if (current < this.commands.size()) {
                    Command next = this.commands.get(current);
                    next.started();
                    this.writer.write(next.toString());
                    this.writer.newLine();
                    this.writer.write("echo " + TOKEN + ' ' + current + " $?");
                    this.writer.newLine();
                    this.writer.flush();
                    current++;
                } else if (this.finish) {
                    this.writer.newLine();
                    this.writer.write("exit");
                    this.writer.newLine();
                    this.writer.flush();
                    this.writer.close();
                    break;
                }
            }
        } catch (InterruptedException exception) {
            exception.printStackTrace();
        }
    }
}
