#ifndef OBSTACLE_H_
#define OBSTACLE_H_

namespace spic {
	/**
	 * @brief Obstacle can be used for obstacle avoidance
	*/
	class Obstacle {
	public:
		Obstacle(const float boundingRadius);

		/**
		 * @brief Needs to declare virtual destructor,
		 *			otherwise can't be used as interface
		 */
		virtual ~Obstacle() = default;
		Obstacle(const Obstacle& other) = delete;
		Obstacle(Obstacle&& other) = delete;
		Obstacle& operator=(const Obstacle& other) = delete;
		Obstacle& operator=(Obstacle&& other) = delete;

		/**
		 * @brief Returns bounding radius of force driven entity.
		 * @return float.
		 * @spicapi
		*/
		float BRadius() const;
	private:
		/**
		 * @brief Bounding radius is used for obstacle avoidance
		*/
		float boundingRadius;
	};
}

#endif // OBSTACLE_H_