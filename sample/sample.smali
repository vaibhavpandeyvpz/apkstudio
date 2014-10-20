.method public static checkCRC32ChkSum()V
    .locals 11
 
    .prologue
    .line 934
    sget-object v9, Lcom/lohan/testtarget/Main;->MyContext:Landroid/content/Context;
 
    invoke-virtual {v9}, Landroid/content/Context;->getPackageCodePath()Ljava/lang/String;
 
    move-result-object v0
 
    .line 935
    .local v0, apkPath:Ljava/lang/String;
    const/4 v3, 0x0
 
    .line 939
    .local v3, chksum:Ljava/lang/Long;
    :try_start_0
    new-instance v7, Ljava/io/FileInputStream;
 
    new-instance v9, Ljava/io/File;
 
    invoke-direct {v9, v0}, Ljava/io/File;-><init>(Ljava/lang/String;)V
 
    invoke-direct {v7, v9}, Ljava/io/FileInputStream;-><init>(Ljava/io/File;)V
 
    .line 940
    .local v7, fis:Ljava/io/FileInputStream;
    new-instance v2, Ljava/util/zip/CRC32;
 
    invoke-direct {v2}, Ljava/util/zip/CRC32;-><init>()V
 
    .line 942
    .local v2, chk:Ljava/util/zip/CRC32;
    new-instance v5, Ljava/util/zip/CheckedInputStream;
 
    invoke-direct {v5, v7, v2}, Ljava/util/zip/CheckedInputStream;-><init>(Ljava/io/InputStream;Ljava/util/zip/Checksum;)V
 
    .line 943
    .local v5, cis:Ljava/util/zip/CheckedInputStream;
    const/16 v9, 0x50
 
    new-array v1, v9, [B
 
    .line 944
    .local v1, buff:[B
    :cond_0
    invoke-virtual {v5, v1}, Ljava/util/zip/CheckedInputStream;->read([B)I
 
    move-result v9
 
    if-gez v9, :cond_0
 
    .line 946
    invoke-virtual {v2}, Ljava/util/zip/CRC32;->getValue()J
 
    move-result-wide v9
 
    invoke-static {v9, v10}, Ljava/lang/Long;->valueOf(J)Ljava/lang/Long;
    :try_end_0
    .catch Ljava/lang/Exception; {:try_start_0 .. :try_end_0} :catch_0
 
    move-result-object v3
 
    .line 953
    .end local v1           #buff:[B
    .end local v2           #chk:Ljava/util/zip/CRC32;
    .end local v5           #cis:Ljava/util/zip/CheckedInputStream;
    .end local v7           #fis:Ljava/io/FileInputStream;
    :goto_0
    const v9, 0x7f040002
 
    invoke-static {v9}, Lcom/lohan/testtarget/PerformTestsTask;->getKeyString(I)Ljava/lang/String;
 
    move-result-object v8
 
    .line 956
    .local v8, keyStrVal:Ljava/lang/String;
    const-string v9, ""
 
    invoke-virtual {v8, v9}, Ljava/lang/String;->equals(Ljava/lang/Object;)Z
 
    .line 960
    invoke-static {v8}, Ljava/lang/Long;->parseLong(Ljava/lang/String;)J
 
    move-result-wide v9
 
    invoke-static {v9, v10}, Ljava/lang/Long;->valueOf(J)Ljava/lang/Long;
 
    move-result-object v4
 
    .line 962
    .local v4, chksumCmp:Ljava/lang/Long;
    invoke-virtual {v3, v4}, Ljava/lang/Long;->equals(Ljava/lang/Object;)Z
 
    .line 970
    return-void
 
    .line 947
    .end local v4           #chksumCmp:Ljava/lang/Long;
    .end local v8           #keyStrVal:Ljava/lang/String;
    :catch_0
    move-exception v9
 
    move-object v6, v9
 
    .line 948
    .local v6, e:Ljava/lang/Exception;
    invoke-virtual {v6}, Ljava/lang/Exception;->printStackTrace()V
 
    goto :goto_0
.end method
 
.method public static checkMD5ChkSum()V
    .locals 12
 
    .prologue
    const/4 v11, 0x0
 
    .line 981
    sget-object v10, Lcom/lohan/testtarget/Main;->MyContext:Landroid/content/Context;
 
    invoke-virtual {v10}, Landroid/content/Context;->getPackageCodePath()Ljava/lang/String;
 
    move-result-object v0
 
    .line 982
    .local v0, apkPath:Ljava/lang/String;
    const/4 v9, 0x0
 
    .line 983
    .local v9, msgDigest:Ljava/security/MessageDigest;
    const/4 v3, 0x0
 
    check-cast v3, [B
 
    .line 985
    .local v3, digest:[B
    :try_start_0
    const-string v10, "MD5"
 
    invoke-static {v10}, Ljava/security/MessageDigest;->getInstance(Ljava/lang/String;)Ljava/security/MessageDigest;
    :try_end_0
    .catch Ljava/security/NoSuchAlgorithmException; {:try_start_0 .. :try_end_0} :catch_0
 
    move-result-object v9
 
    .line 990
    :goto_0
    const/16 v10, 0x2000
 
    new-array v2, v10, [B
 
    .line 992
    .local v2, bytes:[B
    const/4 v6, 0x0
 
    .line 995
    .local v6, fis:Ljava/io/FileInputStream;
    :try_start_1
    new-instance v7, Ljava/io/FileInputStream;
 
    new-instance v10, Ljava/io/File;
 
    invoke-direct {v10, v0}, Ljava/io/File;-><init>(Ljava/lang/String;)V
 
    invoke-direct {v7, v10}, Ljava/io/FileInputStream;-><init>(Ljava/io/File;)V
    :try_end_1
    .catch Ljava/lang/Exception; {:try_start_1 .. :try_end_1} :catch_2
 
    .line 997
    .end local v6           #fis:Ljava/io/FileInputStream;
    .local v7, fis:Ljava/io/FileInputStream;
    :goto_1
    :try_start_2
    invoke-virtual {v7, v2}, Ljava/io/FileInputStream;->read([B)I
 
    move-result v1
 
    .local v1, byteCount:I
    if-gtz v1, :cond_0
 
    .line 1000
    invoke-virtual {v9}, Ljava/security/MessageDigest;->digest()[B
    :try_end_2
    .catch Ljava/lang/Exception; {:try_start_2 .. :try_end_2} :catch_1
 
    move-result-object v3
 
    move-object v6, v7
 
    .line 1005
    .end local v1           #byteCount:I
    .end local v7           #fis:Ljava/io/FileInputStream;
    .restart local v6       #fis:Ljava/io/FileInputStream;
    :goto_2
    const v10, 0x7f040004
 
    invoke-static {v10}, Lcom/lohan/testtarget/PerformTestsTask;->getKeyString(I)Ljava/lang/String;
 
    move-result-object v8
 
    .line 1007
    .local v8, keyStrVal:Ljava/lang/String;
    const-string v10, ""
 
    invoke-virtual {v8, v10}, Ljava/lang/String;->equals(Ljava/lang/Object;)Z
 
    .line 1015
    invoke-static {v8, v11}, Landroid/util/Base64;->decode(Ljava/lang/String;I)[B
 
    move-result-object v10
 
    invoke-static {v10, v3}, Ljava/util/Arrays;->equals([B[B)Z
 
    .line 1020
    return-void
 
    .line 986
    .end local v2           #bytes:[B
    .end local v6           #fis:Ljava/io/FileInputStream;
    .end local v8           #keyStrVal:Ljava/lang/String;
    :catch_0
    move-exception v10
 
    move-object v5, v10
 
    .line 987
    .local v5, e1:Ljava/security/NoSuchAlgorithmException;
    invoke-virtual {v5}, Ljava/security/NoSuchAlgorithmException;->printStackTrace()V
 
    goto :goto_0
 
    .line 998
    .end local v5           #e1:Ljava/security/NoSuchAlgorithmException;
    .restart local v1       #byteCount:I
    .restart local v2       #bytes:[B
    .restart local v7       #fis:Ljava/io/FileInputStream;
    :cond_0
    const/4 v10, 0x0
 
    :try_start_3
    invoke-virtual {v9, v2, v10, v1}, Ljava/security/MessageDigest;->update([BII)V
    :try_end_3
    .catch Ljava/lang/Exception; {:try_start_3 .. :try_end_3} :catch_1
 
    goto :goto_1
 
    .line 1001
    .end local v1           #byteCount:I
    :catch_1
    move-exception v10
 
    move-object v4, v10
 
    move-object v6, v7
 
    .line 1002
    .end local v7           #fis:Ljava/io/FileInputStream;
    .local v4, e:Ljava/lang/Exception;
    .restart local v6       #fis:Ljava/io/FileInputStream;
    :goto_3
    invoke-virtual {v4}, Ljava/lang/Exception;->printStackTrace()V
 
    goto :goto_2
 
    .line 1001
    .end local v4           #e:Ljava/lang/Exception;
    :catch_2
    move-exception v10
 
    move-object v4, v10
 
    goto :goto_3
.end method
 
.method private static asdfgetKeyString(I)Ljava/lang/String;
    .locals 6
    .parameter "resId"
 
    .prologue
    .line 1025
    const-string v2, ""
 
    .line 1028
    .local v2, result:Ljava/lang/String;
    :try_start_0
    sget-object v3, Lcom/lohan/testtarget/Main;->MyContext:Landroid/content/Context;
 
    const-string v4, "your.package.name.key"
 
    const/4 v5, 0x2
 
    invoke-virtual {v3, v4, v5}, Landroid/content/Context;->createPackageContext(Ljava/lang/String;I)Landroid/content/Context;
 
    move-result-object v0
 
    .line 1029
    .local v0, c:Landroid/content/Context;
    invoke-virtual {v0, p0}, Landroid/content/Context;->getString(I)Ljava/lang/String;
    :try_end_0
    .catch Ljava/lang/Exception; {:try_start_0 .. :try_end_0} :catch_0
 
    move-result-object v2
 
    .line 1036
    .end local v0           #c:Landroid/content/Context;
    :goto_0
    return-object v2
 
    .line 1030
    :catch_0
    move-exception v3
 
    move-object v1, v3
 
    .line 1031
    .local v1, e:Ljava/lang/Exception;
    new-instance v3, Ljava/lang/StringBuilder;
 
    const-string v4, "Error while getting key string:\n"
 
    invoke-direct {v3, v4}, Ljava/lang/StringBuilder;-><init>(Ljava/lang/String;)V
 
    invoke-virtual {v3, v1}, Ljava/lang/StringBuilder;->append(Ljava/lang/Object;)Ljava/lang/StringBuilder;
 
    move-result-object v3
 
    invoke-virtual {v3}, Ljava/lang/StringBuilder;->toString()Ljava/lang/String;
 
    move-result-object v3
 
    invoke-static {v3}, Lcom/lohan/testtarget/Console;->log(Ljava/lang/String;)V
 
    .line 1032
    invoke-virtual {v1}, Ljava/lang/Exception;->printStackTrace()V
 
    .line 1033
    const-string v2, ""
 
    goto :goto_0
.end method
