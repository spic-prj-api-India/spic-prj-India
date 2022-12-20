#include "gtest/gtest.h"
#include "BoxCollider.hpp"
#include "CircleCollider.hpp"

using namespace spic;

TEST(BoxColliderTest, SetWidthSuccess) {
	//1. Arrange
	spic::BoxCollider boxCollider = spic::BoxCollider();

	//2. Act
	boxCollider.Width(0.0f);
	boxCollider.Width(1.0f);

	//3. Assert
	EXPECT_EQ(boxCollider.Width(), 1.0f);
}
TEST(BoxColliderTest, SetWidthFailed) {
	//1. Arrange
	spic::BoxCollider boxCollider = spic::BoxCollider();

	//2. Act
	//3. Assert
	EXPECT_THROW({
		try
		{
			boxCollider.Width(-1.0f);
		}
		catch (std::exception e)
		{
			std::string errorMessage = e.what();
			EXPECT_EQ(boxCollider.Width(), 0.0f);
			EXPECT_EQ(errorMessage, "Width can't be below zero");
			throw;
		}
		}, std::range_error);
}
TEST(BoxColliderTest, SetHeightSuccess) {
	//1. Arrange
	spic::BoxCollider boxCollider = spic::BoxCollider();

	//2. Act
	boxCollider.Height(0.0f);
	boxCollider.Height(1.0f);

	//3. Assert
	EXPECT_EQ(boxCollider.Height(), 1.0f);
}
TEST(BoxColliderTest, SetHeightFailed) {
	//1. Arrange
	spic::BoxCollider boxCollider = spic::BoxCollider();

	//2. Act
	//3. Assert
	EXPECT_THROW({
		try
		{
			boxCollider.Height(-1.0f);
		}
		catch (std::exception e)
		{
			std::string errorMessage = e.what();
			EXPECT_EQ(boxCollider.Height(), 0.0f);
			EXPECT_EQ(errorMessage, "Height can't be below zero");
			throw;
		}
		}, std::range_error);
}
TEST(CircleColliderTest, SetRadiusSuccess) {
	//1. Arrange
	spic::CircleCollider circleCollider = spic::CircleCollider();

	//2. Act
	circleCollider.Radius(0.0f);
	circleCollider.Radius(1.0f);

	//3. Assert
	EXPECT_EQ(circleCollider.Radius(), 1.0f);
}
TEST(CircleColliderTest, SetHeightFailed) {
	//1. Arrange
	spic::CircleCollider circleCollider = spic::CircleCollider();

	//2. Act
	//3. Assert
	EXPECT_THROW({
		try
		{
			circleCollider.Radius(-1.0f);
		}
		catch (std::exception e)
		{
			std::string errorMessage = e.what();
			EXPECT_EQ(circleCollider.Radius(), 0.0f);
			EXPECT_EQ(errorMessage, "Radius can't be below zero");
			throw;
		}
		}, std::range_error);
}