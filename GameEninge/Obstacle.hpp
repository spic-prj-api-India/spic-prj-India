#ifndef OBSTACLE_H_
#define OBSTACLE_H_

namespace spic {
	class Obstacle {
	public:
		Obstacle() = default;
		/**
		 * @brief Needs to declare virtual destructor,
		 *			otherwise can't be used as interface
		 */
		virtual ~Obstacle() = default;
		Obstacle(const Obstacle& other) = delete;
		Obstacle(Obstacle&& other) = delete;
		Obstacle& operator=(const Obstacle& other) = delete;
		Obstacle& operator=(Obstacle&& other) = delete;
	};
}

#endif // OBSTACLE_H_