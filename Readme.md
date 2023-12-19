# Status Tree
分层有限状态机变种


## 需求
* 节点容器 TArray -> TSet(兼容class问题?)
* 添加装饰器(参考增强输入系统的装饰器)
    * StatusNode让RootNodes相互链接
    * 让NodeBase不能被子节点Link

* NodeBase::OnEnter前的操作
    * 为StatusTreeComponent::SwitchState多一个IsDelayEnter参数

### 23/12/12
* 修复StatusTreeComponent::IsCurrentStatus判断当前根状态永远为false的Bug
* 新增StatusTreeComponent::bIsDelayEnter(未调试)

### 23/12/10
* 上传