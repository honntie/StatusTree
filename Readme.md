# Status Tree
分层有限状态机变种


## 需求
* _Foreach_Valid_Node_宏改成TArray::FilterByPredicate
    * 方案2 在初始化时把空节点删了
* 添加装饰器(参考增强输入系统的装饰器)
    * StatusNode让RootNodes相互链接
    * 让NodeBase不能被子节点Link


### 23/12/23
* StatusTreeComponent增加IsCurrentRoot函数


### 23/12/20
* 否决TSet当节点容器
* 为StatusTreeComponent::SwitchState多一个IsEnterLated参数
* 移除StatusTreeComponent::bIsDelayEnter
* UStateNode::IsExit升级到UNodeBase::IsExit
* 修复StatusNode的GetCondition和GetTransition无效问题
* 为UStateNode::CanReentry做特殊处理


### 23/12/12
* 修复StatusTreeComponent::IsCurrentStatus判断当前根状态永远为false的Bug
* 新增StatusTreeComponent::bIsDelayEnter(未调试)

### 23/12/10
* 上传