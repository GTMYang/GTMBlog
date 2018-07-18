
CAKeyframeAnimation的calculationMode属性理解
===

calculationMode,计算模式.其主要针对的是每一帧的内容为一个座标点的情况,也就是对anchorPoint 和 position 进行的动画.当在平面座标系中有多个离散的点的时候,可以是离散的,也可以直线相连后进行插值计算,也可以使用圆滑的曲线将他们相连后进行插值计算. calculationMode目前提供如下几种模式：

* **kCAAnimationLinear** 当关键帧为座标点的时候,关键帧之间直接直线相连进行插值计算（calculationMode的默认值）;
* **kCAAnimationDiscrete** 不进行插值计算,所有关键帧直接逐个进行显示;
* **kCAAnimationPaced** 动画均匀进行,而不是按keyTimes设置的或者按关键帧平分时间,此时keyTimes和timingFunctions无效;
* **kCAAnimationCubic** 对关键帧为座标点的关键帧进行圆滑曲线相连后插值计算,对于曲线的形状还可以通过tensionValues,continuityValues,biasValues来进行调整自定义,这里的数学原理是Kochanek–Bartels spline,这里的主要目的是使得运行的轨迹变得圆滑;
* **kCAAnimationCubicPaced** 在kCAAnimationCubic的基础上使得动画运行变得均匀,就是系统时间内运动的距离相同,此时keyTimes以及timingFunctions也是无效的.
