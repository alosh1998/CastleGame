// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef LEARNINGPROJECT_Main_generated_h
#error "Main.generated.h already included, missing '#pragma once' in Main.h"
#endif
#define LEARNINGPROJECT_Main_generated_h

#define LearningProject_Cpy_Source_LearningProject_Main_h_34_SPARSE_DATA
#define LearningProject_Cpy_Source_LearningProject_Main_h_34_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execDeathEnd); \
	DECLARE_FUNCTION(execPlaySwingSound); \
	DECLARE_FUNCTION(execAttackEnd); \
	DECLARE_FUNCTION(execIncrementHealth); \
	DECLARE_FUNCTION(execIncrementCoin); \
	DECLARE_FUNCTION(execShowPickupLcoations);


#define LearningProject_Cpy_Source_LearningProject_Main_h_34_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execDeathEnd); \
	DECLARE_FUNCTION(execPlaySwingSound); \
	DECLARE_FUNCTION(execAttackEnd); \
	DECLARE_FUNCTION(execIncrementHealth); \
	DECLARE_FUNCTION(execIncrementCoin); \
	DECLARE_FUNCTION(execShowPickupLcoations);


#define LearningProject_Cpy_Source_LearningProject_Main_h_34_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAMain(); \
	friend struct Z_Construct_UClass_AMain_Statics; \
public: \
	DECLARE_CLASS(AMain, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/LearningProject"), NO_API) \
	DECLARE_SERIALIZER(AMain)


#define LearningProject_Cpy_Source_LearningProject_Main_h_34_INCLASS \
private: \
	static void StaticRegisterNativesAMain(); \
	friend struct Z_Construct_UClass_AMain_Statics; \
public: \
	DECLARE_CLASS(AMain, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/LearningProject"), NO_API) \
	DECLARE_SERIALIZER(AMain)


#define LearningProject_Cpy_Source_LearningProject_Main_h_34_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AMain(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AMain) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AMain); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AMain); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AMain(AMain&&); \
	NO_API AMain(const AMain&); \
public:


#define LearningProject_Cpy_Source_LearningProject_Main_h_34_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AMain(AMain&&); \
	NO_API AMain(const AMain&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AMain); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AMain); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AMain)


#define LearningProject_Cpy_Source_LearningProject_Main_h_34_PRIVATE_PROPERTY_OFFSET
#define LearningProject_Cpy_Source_LearningProject_Main_h_31_PROLOG
#define LearningProject_Cpy_Source_LearningProject_Main_h_34_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	LearningProject_Cpy_Source_LearningProject_Main_h_34_PRIVATE_PROPERTY_OFFSET \
	LearningProject_Cpy_Source_LearningProject_Main_h_34_SPARSE_DATA \
	LearningProject_Cpy_Source_LearningProject_Main_h_34_RPC_WRAPPERS \
	LearningProject_Cpy_Source_LearningProject_Main_h_34_INCLASS \
	LearningProject_Cpy_Source_LearningProject_Main_h_34_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define LearningProject_Cpy_Source_LearningProject_Main_h_34_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	LearningProject_Cpy_Source_LearningProject_Main_h_34_PRIVATE_PROPERTY_OFFSET \
	LearningProject_Cpy_Source_LearningProject_Main_h_34_SPARSE_DATA \
	LearningProject_Cpy_Source_LearningProject_Main_h_34_RPC_WRAPPERS_NO_PURE_DECLS \
	LearningProject_Cpy_Source_LearningProject_Main_h_34_INCLASS_NO_PURE_DECLS \
	LearningProject_Cpy_Source_LearningProject_Main_h_34_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> LEARNINGPROJECT_API UClass* StaticClass<class AMain>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID LearningProject_Cpy_Source_LearningProject_Main_h


#define FOREACH_ENUM_ESTAMINASTATUS(op) \
	op(EStaminaStatus::ESS_Normal) \
	op(EStaminaStatus::ESS_BelowMinimum) \
	op(EStaminaStatus::ESS_Exhausted) \
	op(EStaminaStatus::ESS_ExhaustedRecovering) 

enum class EStaminaStatus : uint8;
template<> LEARNINGPROJECT_API UEnum* StaticEnum<EStaminaStatus>();

#define FOREACH_ENUM_EMOVEMENTSTATUS(op) \
	op(EMovementStatus::EMS_Normal) \
	op(EMovementStatus::EMS_Sprinting) \
	op(EMovementStatus::EMS_Dead) 

enum class EMovementStatus : uint8;
template<> LEARNINGPROJECT_API UEnum* StaticEnum<EMovementStatus>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
