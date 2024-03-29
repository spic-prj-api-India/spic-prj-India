#ifndef OBSTACLE_H_
#define OBSTACLE_H_

namespace spic {
	/**
	 * @brief Obstacle can be used for obstacle avoidance
	*/
	class Obstacle {
	public:
		/**
		 * @brief Constructor
		 * @param boundingRadius Bounding radius is radius of the bounds around entity
		*/
		Obstacle(const float boundingRadius);

		/**
		 * @brief Needs to declare virtual destructor,
		 *			otherwise can't be used as interface
		 */
		virtual ~Obstacle() = default;
		Obstacle(const Obstacle& other) = default;
		Obstacle(Obstacle&& other) = default;
		virtual Obstacle& operator=(const Obstacle& other) = default;
		virtual Obstacle& operator=(Obstacle&& other) = default;

		/**
		 * @brief Returns bounding radius of force driven entity.
		 * @return float.
		 * @spicapi
		*/
		float BRadius() const;
	private:
		/**
		 * @brief Bounding radius is the radius of the bounds around entity.
					Bouding radius is used for obstacle avoidance
		*/
		float boundingRadius;
	};
}

#endif // OBSTACLE_H_