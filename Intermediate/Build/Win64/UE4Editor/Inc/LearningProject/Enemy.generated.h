// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UPrimitiveComponent;
class AActor;
struct FHitResult;
class AMain;
#ifdef LEARNINGPROJECT_Enemy_generated_h
#error "Enemy.generated.h already included, missing '#pragma once' in Enemy.h"
#endif
#define LEARNINGPROJECT_Enemy_generated_h

#define LearningProject_Cpy_Source_LearningProject_Enemy_h_21_SPARSE_DATA
#define LearningProject_Cpy_Source_LearningProject_Enemy_h_21_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execDeathEnd); \
	DECLARE_FUNCTION(execAttackend); \
	DECLARE_FUNCTION(execDeactivateCollision); \
	DECLARE_FUNCTION(execActivateCollision); \
	DECLARE_FUNCTION(execCombatOnOverlapEnd); \
	DECLARE_FUNCTION(execCombatOnOverlapBegin); \
	DECLARE_FUNCTION(execMoveToTarget); \
	DECLARE_FUNCTION(execCombatSphereOnOverlapEnd); \
	DECLARE_FUNCTION(execCombatSphereOnOverlapBegin); \
	DECLARE_FUNCTION(execAgroSphereOnOverlapEnd); \
	DECLARE_FUNCTION(execAgroSphereOnOverlapBegin);


#define LearningProject_Cpy_Source_LearningProject_Enemy_h_21_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execDeathEnd); \
	DECLARE_FUNCTION(execAttackend); \
	DECLARE_FUNCTION(execDeactivateCollision); \
	DECLARE_FUNCTION(execActivateCollision); \
	DECLARE_FUNCTION(execCombatOnOverlapEnd); \
	DECLARE_FUNCTION(execCombatOnOverlapBegin); \
	DECLARE_FUNCTION(execMoveToTarget); \
	DECLARE_FUNCTION(execCombatSphereOnOverlapEnd); \
	DECLARE_FUNCTION(execCombatSphereOnOverlapBegin); \
	DECLARE_FUNCTION(execAgroSphereOnOverlapEnd); \
	DECLARE_FUNCTION(execAgroSphereOnOverlapBegin);


#define LearningProject_Cpy_Source_LearningProject_Enemy_h_21_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAEnemy(); \
	friend struct Z_Construct_UClass_AEnemy_Statics; \
public: \
	DECLARE_CLASS(AEnemy, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/LearningProject"), NO_API) \
	DECLARE_SERIALIZER(AEnemy)


#define LearningProject_Cpy_Source_LearningProject_Enemy_h_21_INCLASS \
private: \
	static void StaticRegisterNativesAEnemy(); \
	friend struct Z_Construct_UClass_AEnemy_Statics; \
public: \
	DECLARE_CLASS(AEnemy, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/LearningProject"), NO_API) \
	DECLARE_SERIALIZER(AEnemy)


#define LearningProject_Cpy_Source_LearningProject_Enemy_h_21_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AEnemy(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AEnemy) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AEnemy); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AEnemy); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AEnemy(AEnemy&&); \
	NO_API AEnemy(const AEnemy&); \
public:


#define LearningProject_Cpy_Source_LearningProject_Enemy_h_21_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AEnemy(AEnemy&&); \
	NO_API AEnemy(const AEnemy&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AEnemy); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AEnemy); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AEnemy)


#define LearningProject_Cpy_Source_LearningProject_Enemy_h_21_PRIVATE_PROPERTY_OFFSET
#define LearningProject_Cpy_Source_LearningProject_Enemy_h_18_PROLOG
#define LearningProject_Cpy_Source_LearningProject_Enemy_h_21_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	LearningProject_Cpy_Source_LearningProject_Enemy_h_21_PRIVATE_PROPERTY_OFFSET \
	LearningProject_Cpy_Source_LearningProject_Enemy_h_21_SPARSE_DATA \
	LearningProject_Cpy_Source_LearningProject_Enemy_h_21_RPC_WRAPPERS \
	LearningProject_Cpy_Source_LearningProject_Enemy_h_21_INCLASS \
	LearningProject_Cpy_Source_LearningProject_Enemy_h_21_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define LearningProject_Cpy_Source_LearningProject_Enemy_h_21_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	LearningProject_Cpy_Source_LearningProject_Enemy_h_21_PRIVATE_PROPERTY_OFFSET \
	LearningProject_Cpy_Source_LearningProject_Enemy_h_21_SPARSE_DATA \
	LearningProject_Cpy_Source_LearningProject_Enemy_h_21_RPC_WRAPPERS_NO_PURE_DECLS \
	LearningProject_Cpy_Source_LearningProject_Enemy_h_21_INCLASS_NO_PURE_DECLS \
	LearningProject_Cpy_Source_LearningProject_Enemy_h_21_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> LEARNINGPROJECT_API UClass* StaticClass<class AEnemy>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID LearningProject_Cpy_Source_LearningProject_Enemy_h


#define FOREACH_ENUM_EENEMYMOVMENTSTATUS(op) \
	op(EEnemyMovmentStatus::EMS_Idle) \
	op(EEnemyMovmentStatus::EMS_MoveToTarget) \
	op(EEnemyMovmentStatus::EMS_Attacking) \
	op(EEnemyMovmentStatus::EMS_Dead) 

enum class EEnemyMovmentStatus : uint8;
template<> LEARNINGPROJECT_API UEnum* StaticEnum<EEnemyMovmentStatus>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
