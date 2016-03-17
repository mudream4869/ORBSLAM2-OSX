## forked from https://github.com/raulmur/ORB_SLAM2

安装opencv以及eigen依赖后，直接打开xcodeproject运行即可。
（其余依赖包含在代码中，不需要dataset, 但是需要修改include以及link path）

运行视频： http://7xnvhc.com1.z0.glb.clouddn.com/orbslammac1.m4v

对应ORBSLAM2技术文章和代码分析：http://zhuanlan.zhihu.com/computercoil/20589372


####  依赖: 

基于OSX 10.11 opencv 3.1.0 Eigen3,也可以使用其他版本

可以使用 "brew install opencv3"  "brew install eigen" 安装opencv3 和 eigen，
其他依赖（g2o dbow2）已经包含在代码中


####修改
* 去掉了Pangolin.
* 去掉了cmake, 直接打开 ORB_SLAM2.xcodeproj 编译运行即可.
* 去掉了MapDrawer FrameDrawer.
* 使用二进制词典优化加载速度(来自 https://github.com/poine/ORB_SLAM2)
* 去掉了dataset，使用摄像头即时处理图像
* 代码中仅留有单目方法

#### dependency: 

OSX 10.11 opencv 3.1.0 Eigen3

Can be installed with "brew install opencv3"  "brew install eigen"


####changes
* Pangolin removed.
* cmake system removed, open ORB_SLAM2.xcodeproj and build system with dependencies.
* MapDrawer FrameDrawer removed.
* binnary dictionary to speed up loading (from https://github.com/poine/ORB_SLAM2)
* camera capture instead of datasets
* only monocular method.
