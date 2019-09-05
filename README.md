# Qt Declarative (Quick 2)

### MOD for SAO Utils

- 修复 [QTBUG-73843](https://bugreports.qt.io/browse/QTBUG-73843)
- 私有导出 QQuickScreenInfo 和 QQuickScreen
- QQuickAbstractAnimation::threadingModel() 默认返回 AnyThread
- QQuickWindowQmlImpl: 当启用渲染控制时，使用真实的 transient parent 窗口
