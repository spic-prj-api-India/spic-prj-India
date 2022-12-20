#include "gtest/gtest.h"
#include "RigidBody.hpp"

using namespace spic;

TEST(RigidBodyTest, ConstructorSuccess) {
	//1. Arrange
	//2. Act
	spic::RigidBody rigidBody = spic::RigidBody(0.0f, 0.0f, spic::BodyType::dynamicBody);

	//3. Assert
	EXPECT_EQ(rigidBody.Mass(), 0.0f);
	EXPECT_EQ(rigidBody.GravityScale(), 0.0f);
	EXPECT_EQ(rigidBody.BodyType(), spic::BodyType::dynamicBody);
}
TEST(RigidBodyTest, ConstructorFailedNegativeMass) {
	//1. Arrange
	//2. Act
	//3. Assert
	EXPECT_THROW({
		try
		{
			spic::RigidBody rigidBody = spic::RigidBody(-1.0f, 0.0f, spic::BodyType::dynamicBody);
		}
		catch (std::exception e)
		{
			std::string errorMessage = e.what();
			EXPECT_EQ(errorMessage, "Mass can't be below zero");
			throw;
		}
		}, std::range_error);
}
TEST(RigidBodyTest, ConstructorFailedNegativeGravityScale) {
	//1. Arrange
	//2. Act
	//3. Assert
	EXPECT_THROW({
		try
		{
			spic::RigidBody rigidBody = spic::RigidBody(0.0f, -1.0f, spic::BodyType::dynamicBody);
		}
		catch (std::exception e)
		{
			std::string errorMessage = e.what();
			EXPECT_EQ(errorMessage, "Gravity scale can't be below zero");
			throw;
		}
		}, std::range_error);
}

TEST(RigidBodyTest, SetMassSuccess) {
	//1. Arrange
	spic::RigidBody rigidBody = spic::RigidBody(0.0f, 0.0f, spic::BodyType::dynamicBody);

	//2. Act
	rigidBody.Mass(1.0f);

	//3. Assert
	EXPECT_EQ(rigidBody.Mass(), 1.0f);
}
TEST(RigidBodyTest, SetMassFailed) {
	//1. Arrange
	spic::RigidBody rigidBody = spic::RigidBody(0.0f, 0.0f, spic::BodyType::dynamicBody);

	//2. Act
	//3. Assert
	EXPECT_THROW({
		try
		{
			rigidBody.Mass(-1.0f);
		}
		catch (std::exception e)
		{
			std::string errorMessage = e.what();
			EXPECT_EQ(rigidBody.Mass(), 0.0f);
			EXPECT_EQ(errorMessage, "Mass can't be below zero");
			throw;
		}
		}, std::range_error);
}
TEST(RigidBodyTest, SetGravityScaleSuccess) {
	//1. Arrange
	spic::RigidBody rigidBody = spic::RigidBody(0.0f, 0.0f, spic::BodyType::dynamicBody);

	//2. Act
	rigidBody.GravityScale(1.0f);

	//3. Assert
	EXPECT_EQ(rigidBody.GravityScale(), 1.0f);
}
TEST(RigidBodyTest, SetGravityScaleFailed) {
	//1. Arrange
	spic::RigidBody rigidBody = spic::RigidBody(0.0f, 0.0f, spic::BodyType::dynamicBody);

	//2. Act
	//3. Assert
	EXPECT_THROW({
		try
		{
			rigidBody.GravityScale(-1.0f);
		}
		catch (std::exception e)
		{
			std::string errorMessage = e.what();
			EXPECT_EQ(rigidBody.GravityScale(), 0.0f);
			EXPECT_EQ(errorMessage, "Gravity scale can't be below zero");
			throw;
		}
		}, std::range_error);
}