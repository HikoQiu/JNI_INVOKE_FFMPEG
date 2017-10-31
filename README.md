# JNI_INVOKE_FFMPEG

Use Ffmpeg to deal with videos in android.

本人实验过程步骤：

### 一，步骤概览

 - 1, 准备开发环境和工具；其中包括：Android开发环境(Eclipse)、安装NDK。
 - 2, 下载并解压ffmpeg源代码
 - 3, 编译ffmpeg源码，生成类文件(*.so)供后面Andoid项目使用
 - 4, 创建Android项目(MyJni)并配置JNI开发的相关文件
 - 5, 引入第3步生成的ffmpeg相关的类文件(*.so)
 - 6, Java调用JNI的C代码(C代码调用ffmpeg)进行视频压缩  
 
### 二，步骤详细

本次试验的开发环境和相关版本：

 - Mac OS X YOSEMITE 10.10.5
 - Eclipse Mars.1 Release (4.5.1)
 - cc(gcc) 版本(cc -v)  
    Apple LLVM version 7.0.0 (clang-700.1.76)  
    Target: x86_64-apple-darwin14.5.0  
    Thread model: posix  
 - make 版本 (make -v)  
 	GNU Make 3.81
 - ffmpeg 2.8.4
 - android-ndk-r10e-darwin-x86_64.bin
 
#### 1， 准备相关的环境和工具；

 - **Android 开发环境(JDK)**

配置Android开发环境，以及安装必要的JDK / [JDK 下载地址](http://developer.android.com/sdk/index.html)。Android开发环境具体操作请Google 自行解决。

 - **NDK**

下载并解压NDK，具体参考Android Developers / [Android NDK 下载地址](http://developer.android.com/tools/sdk/ndk/index.html)。

解压后将得到一个NDK的解压目录，比如我的是：/Users/hikoqiu/packages/android-ndk-r10e  

备注： 后面将使用`$NDK`来代表NDK的目录， 比如：$NDK/ndk-build 则表示/Users/hikoqiu/packages/android-ndk-r10e/ndk-build

#### 2， 准备ffmpeg源码

 - ffmpeg的源码可以从ffmpeg官网下载 / [ffmpeg官网](http://www.ffmpeg.org/download.html)
 - 解压下载的文件  
   我使用的是 ffmpeg-2.8.4.tar.bz2  
   解压： **tar -xf ffmpeg-2.8.4.tar.bz2**
   
将解压后的源码文件夹复制到$NDK/sources目录，此时$NDK/sources目录下就有ffmpeg-2.8.4这个源码文件夹($NDK/sources/ffmpeg-2.8.4).  

*为了目录好看，我把ffmpeg-2.8.4改名为ffmpeg*

#### 3, 编译ffmpeg源代码

 - **修改源码中的configure文件**
 
 网上的说法是：为了让ffmpeg源码能顺利编译并用于android，需要修改configure文件的几个参数。
 
 将#NDK/sources/ffmpeg/configure中的以下4个变量：

> SLIBNAME_WITH_MAJOR='$(SLIBNAME).$(LIBMAJOR)'  
> LIB_INSTALL_EXTRA_CMD='$$(RANLIB) "$(LIBDIR)/$(LIBNAME)"'  
> SLIB_INSTALL_NAME='$(SLIBNAME_WITH_VERSION)'  
> SLIB_INSTALL_LINKS='$(SLIBNAME_WITH_MAJOR) $(SLIBNAME)'  

修改成:

> SLIBNAME_WITH_MAJOR='$(SLIBPREF)$(FULLNAME)-$(LIBMAJOR)$(SLIBSUF)'  
> LIB_INSTALL_EXTRA_CMD='$$(RANLIB) "$(LIBDIR)/$(LIBNAME)"'  
> SLIB_INSTALL_NAME='$(SLIBNAME_WITH_MAJOR)'  
> SLIB_INSTALL_LINKS='$(SLIBNAME)'  


 - **新建shell文件: build_ffmpeg.sh**  
  
  在`$NDK/sources/ffmpeg`目录下新建build_ffmpeg.sh文件，文件具体内容请参考：[build_ffmpeg.sh](https://github.com/HikoQiu/JNI_INVOKE_FFMPEG/blob/master/scripts/build_ffmpeg.sh).  
  
  *因为我使用Markdown写这篇文，格式不好控制，所以这里就不贴出来代码，请直接点连接查看。*
   
   **注意**：build_ffmpeg.sh中三个变量NDK、SYSROOT、TOOLCHAIN的需要根据你具体的NDK的解压路径进行配置。


 - **编译ffmpeg**
 
   先给build_ffmpeg.sh加上可执行的权限，再执行。
   
   > chmod a+x build_ffmpeg.sh  
   > ./build_ffmpeg.sh

备注：build_ffmpeg.sh文件中配置了./configure的一些相关参数, 然后make、make install.

顺利执行完之后，将会在$NDK/sources/ffmpeg/android/arm/lib下看到多个.so文件，在lib目录下还有多个软链文件。


 - **配置Android.mk, 让编译的.so文件能供项目使用**

在$NDK/sources/ffmpeg/android/arm目录下创建Android.mk文件，文件内容请参考: [Android.mk](https://github.com/HikoQiu/JNI_INVOKE_FFMPEG/blob/master/scripts/arm/Android.mk)  

备注：配置在Android.mk的相关的.so类文件，将会在后面的操作`$NDK/ndk-build`中，复制到项目的libs里面。

#### 4， 创建实验的Android项目并配置JNI

 - **创建Android项目**
 
 比如创建项目: MyJni
 
 - **配置jni & Android.mk**
  
    i, 在项目的根目录创建`jni`目录，比如：MyJni/jni  
    ii, 在刚创建的jni目录下创建`Android.mk`文件，比如：MyJni/jni/Android.mk  
    
    Android.mk具体内容，请参考：[Android.mk](https://github.com/HikoQiu/JNI_INVOKE_FFMPEG/blob/master/scripts/jni/Android.mk)  
    
    备注：Android.mk中多个变量的解释：  
         LOCAL_MODULE // 编译后的文件名  
         LOCAL_C_INCLUDE // 编译所依赖的相关ffmpeg的头文件，具体路径要根据自己的文件路径  
         LOCAL_SRC_FILES // 编译的文件
         
    **注意：** 因为我这里直接将原来的ffmpeg/目录下的几个文件也拷贝过来( 项目的jni目录结构见：[JNI_INVOKE_FFMPEG jni目录](https://github.com/HikoQiu/JNI_INVOKE_FFMPEG/tree/master/jni) )，然后再在jni的C代码中自定义了一个方法直接调用原来ffmpeg.c中的main()方法，这样，我就能直接从Java中传一个命令进行执行ffmpeg的操作。比如：ffmpeg -y -i /storage/emulated/0/appwonderroot/v/raw/vedio-1586478489.mp4 -strict experimental -r 30 -vcodec mpeg4 -b 50000 /storage/emulated/0/appwonderroot/v/cps/abc.mp4  
    
    如果你不想跟我一样的调用方式，像独立去操作每个类暴露的方法，可以不用像上面的Android.mk那样配置。
    
#### 5, 引用.so文件，并在Java中调用

这部分更多是JNI的开发，可以去参考其他JNI的开发资料。


这里使用MyJni项目来介绍。

 - 创建一个类，Loader.java ( 参考： [Loader.java](https://github.com/HikoQiu/JNI_INVOKE_FFMPEG/blob/master/src/com/example/myjni/Loader.java) ).
 
 - 生成Loader.java的JNI头部文件。  
    
   进入MyJni/bin/classes目录，使用 `javah -classpath . -jni com.example.myjni.Loader`生成JNI的头部文件，并把生成的*.h文件移到MyJni/jni目录下，其实就是个C头部文件，如：[com_example_myjni_Loader.h](https://github.com/HikoQiu/JNI_INVOKE_FFMPEG/blob/master/jni/com_example_myjni_Loader.h)
   
 - 编译自定义的JNI方法和ffmpeg的类文件
 
   i. 进入项目MyJni  
   ii. 执行$NDK/ndk-build
   
   这个时候，顺利的话，会在MyJni的libs下生成多个ffmpeg的相关的类文件(.so).
   
#### 6，调用

在Loader.java中调用，具体请参考 [Loader.java](https://github.com/HikoQiu/JNI_INVOKE_FFMPEG/blob/master/src/com/example/myjni/Loader.java)

一切顺利的话，将会看到压缩之后的视频文件，20+M的视频文件，只剩下3M，而且还不是很模糊。


### 三，参考资料


如果上面你看不懂或者操作失败，那一定是我介绍得不清楚。这里有更多可以参考的资料，这是我在做这个实验的过程中参考的内容。

在做这个实验的时候，参考了很多很多内容，从普通的博客到多个的stackoverflow的内容，中间遇到了接近无数个问题，最终顺利弄出来。文件的所有代码以及我的测试项目的文件都已经放在我的github上，见：[JNI_INVOKE_FFMPEG](https://github.com/HikoQiu/JNI_INVOKE_FFMPEG) .

我平时是一个服务端+后端工程师，所以玩Android都是业余时间试试而已，所以优化之类的工作需要靠各位Android的工程师了。

 - [Integrate FFMPEG library in Android](http://ffmpeg-android.blogspot.com/) // 需要梯子，这篇很有引导性，建议先看这篇  
 - [Compile FFmpeg for Android](http://enoent.fr/blog/2014/06/20/compile-ffmpeg-for-android/)  // 在自定义的jni C代码中调用ffmpeg.c中的main()方法的主意，就是从这篇文中来的。  
 - [ FFmpeg的Android平台移植—编译篇](http://blog.csdn.net/gobitan/article/details/22750719)
   

