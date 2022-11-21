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
#ifdef LEARNINGPROJECT_Weapon_generated_h
#error "Weapon.generated.h already included, missing '#pragma once' in Weapon.h"
#endif
#define LEARNINGPROJECT_Weapon_generated_h

#define LearningProject_Cpy_Source_LearningProject_Weapon_h_22_SPARSE_DATA
#define LearningProject_Cpy_Source_LearningProject_Weapon_h_22_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execDeactivateCollision); \
	DECLARE_FUNCTION(execActivateCollision); \
	DECLARE_FUNCTION(execCombatOnOverlapEnd); \
	DECLARE_FUNCTION(execCombatOnOverlapBegin);


#define LearningProject_Cpy_Source_LearningProject_Weapon_h_22_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execDeactivateCollision); \
	DECLARE_FUNCTION(execActivateCollision); \
	DECLARE_FUNCTION(execCombatOnOverlapEnd); \
	DECLARE_FUNCTION(execCombatOnOverlapBegin);


#define LearningProject_Cpy_Source_LearningProject_Weapon_h_22_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAWeapon(); \
	friend struct Z_Construct_UClass_AWeapon_Statics; \
public: \
	DECLARE_CLASS(AWeapon, AItem, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/LearningProject"), NO_API) \
	DECLARE_SERIALIZER(AWeapon)


#define LearningProject_Cpy_Source_LearningProject_Weapon_h_22_INCLASS \
private: \
	static void StaticRegisterNativesAWeapon(); \
	friend struct Z_Construct_UClass_AWeapon_Statics; \
public: \
	DECLARE_CLASS(AWeapon, AItem, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/LearningProject"), NO_API) \
	DECLARE_SERIALIZER(AWeapon)


#define LearningProject_Cpy_Source_LearningProject_Weapon_h_22_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AWeapon(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AWeapon) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AWeapon); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AWeapon); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AWeapon(AWeapon&&); \
	NO_API AWeapon(const AWeapon&); \
public:


#define LearningProject_Cpy_Source_LearningProject_Weapon_h_22_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AWeapon(AWeapon&&); \
	NO_API AWeapon(const AWeapon&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AWeapon); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AWeapon); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AWeapon)


#define LearningProject_Cpy_Source_LearningProject_Weapon_h_22_PRIVATE_PROPERTY_OFFSET
#define LearningProject_Cpy_Source_LearningProject_Weapon_h_19_PROLOG
#define LearningProject_Cpy_Source_LearningProject_Weapon_h_22_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	LearningProject_Cpy_Source_LearningProject_Weapon_h_22_PRIVATE_PROPERTY_OFFSET \
	LearningProject_Cpy_Source_LearningProject_Weapon_h_22_SPARSE_DATA \
	LearningProject_Cpy_Source_LearningProject_Weapon_h_22_RPC_WRAPPERS \
	LearningProject_Cpy_Source_LearningProject_Weapon_h_22_INCLASS \
	LearningProject_Cpy_Source_LearningProject_Weapon_h_22_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define LearningProject_Cpy_Source_LearningProject_Weapon_h_22_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	LearningProject_Cpy_Source_LearningProject_Weapon_h_22_PRIVATE_PROPERTY_OFFSET \
	LearningProject_Cpy_Source_LearningProject_Weapon_h_22_SPARSE_DATA \
	LearningProject_Cpy_Source_LearningProject_Weapon_h_22_RPC_WRAPPERS_NO_PURE_DECLS \
	LearningProject_Cpy_Source_LearningProject_Weapon_h_22_INCLASS_NO_PURE_DECLS \
	LearningProject_Cpy_Source_LearningProject_Weapon_h_22_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> LEARNINGPROJECT_API UClass* StaticClass<class AWeapon>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID LearningProject_Cpy_Source_LearningProject_Weapon_h


#define FOREACH_ENUM_EWEAPONSTATE(op) \
	op(EWeaponState::EWS_Pickup) \
	op(EWeaponState::EWS_Equipped) 

enum class EWeaponState : uint8;
template<> LEARNINGPROJECT_API UEnum* StaticEnum<EWeaponState>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
