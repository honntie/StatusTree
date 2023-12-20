// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "NodeBase.generated.h"

#define _Foreach_Valid_Node_(Nodes, Exec) \
    for (int i = 0; i < Nodes.Num(); i++) {\
        UNodeBase* Node = Nodes[i]; \
        if (!IsValid(Node)) continue; \
        Exec \
    }


class UStatusTreeComponent;
/**
 * 
 */
UCLASS(NotBlueprintable, NotBlueprintType, DefaultToInstanced, EditInlineNew, meta=(BlueprintThreadSafe))
class STATUSTREE_API UNodeBase : public UObject
{
	GENERATED_BODY()
	
#pragma region 蓝图成员/函数
public:
	UPROPERTY(EditDefaultsOnly, Instanced, Category="Nodes", meta=(ToolTip = "单向链接状态"))
	TArray<class UNodeBase*> NextNodes;  

	UPROPERTY(EditDefaultsOnly, Category="Property", meta=(ToolTip = "是否链接同层的左侧节点"))
	bool LinkPrev = false; 

	UPROPERTY(EditDefaultsOnly, Category="Property", meta=(ToolTip = "是否链接同层的右侧节点"))
	bool LinkNext = false;

	UPROPERTY(EditDefaultsOnly, Category="Property", meta=(ToolTip = "是否链接上一个节点"))
	bool LinkLast = false;    

	UPROPERTY(EditDefaultsOnly, Category="Property", meta=(ToolTip="是否可当做出口"))
	bool IsExit = false;   

	UFUNCTION(BlueprintCallable, meta=(DeterminesOutputType = "Type"))
	UNodeBase* GetStatus(TSubclassOf<UNodeBase> Type) const;

protected:
	UPROPERTY(BlueprintReadOnly, Category="Property", meta=(ToolTip = "驱动该状态的状态树"))
	UStatusTreeComponent *StatusTree;    // 驱动该状态的状态树
	
#pragma endregion

#pragma region 蓝图可重写函数
public:
	/**
	 * @brief 初始化时调用该函数
	 */
	UFUNCTION(BlueprintNativeEvent)
	void OnInit();
	virtual void OnInit_Implementation() {}

	/**
	 * @brief 进入状态时前执行
	 */
	UFUNCTION(BlueprintNativeEvent)
	void OnEnter();
	virtual void OnEnter_Implementation() {}

	/**
	 * @brief 进入状态后每帧执行
	 * @param DeltaTime 每当帧执行所需时间
	 */
	UFUNCTION(BlueprintNativeEvent)
	void OnUpdate(float DeltaTime);
	virtual void OnUpdate_Implementation(float DeltaTime) {}

	/**
	 * @brief 退出状态时执行
	 */
	UFUNCTION(BlueprintNativeEvent)
	void OnExit();
	virtual void OnExit_Implementation() {}
	
	/**
	 * @brief 该状态的进入条件
	 * @return 是否可进入条件(默认返回true)
	 */
	UFUNCTION(BlueprintNativeEvent)
	bool GetCondition() const;
	virtual bool GetCondition_Implementation() const { return true; }

	/**
	 * @brief 该状态的过渡(离开)条件
	 * @param Type 下一个状态的类型
	 * @return 是否可进入条件(默认返回true)
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool GetTransition(TSubclassOf<UNodeBase> Type) const;
	virtual bool GetTransition_Implementation(TSubclassOf<UNodeBase> Type) const { return true; }
#pragma endregion
	
#pragma region 非暴露蓝图部分
public:
	UNodeBase* Status = nullptr;    // 所属状态

	/**
	 * @brief 状态初始化
	 * @param User 使用该状态的状态树
	 */
	virtual void Init(UStatusTreeComponent* User);
	
	/**
	 * @brief 返回当前状态的Status组, 层次越低所在的位置越靠前
	 * @return Status数组
	 */
	TArray<UNodeBase*> GetStatusLayers() const;
	
	/**
	 * @brief 在自身寻找下一个状态, 寻找顺序为self->NextNode->Status
	 * @param Type 状态类型
	 * @return 正确的状态, 如果状态不存在返回nullptr
	 */
	virtual UNodeBase* FindNextState(TSubclassOf<UNodeBase> Type) const;
	
	/**
	 * @brief 设置Status
	 * @param StatusNode Status节点
	 */
	void SetStatus(UNodeBase* StatusNode);

	/**
	 * @brief 匹配所需节点的类型
	 * @param Type 匹配类型
	 * @return 返回相匹配的节点, 如果没有则返回nullptr
	 */
	virtual UNodeBase* Match(TSubclassOf<UNodeBase> Type) const { return const_cast<UNodeBase*>(this); }
#pragma endregion
};
