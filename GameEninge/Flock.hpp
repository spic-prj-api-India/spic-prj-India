#ifndef FLOCK_H_
#define FLOCK_H_

#include <string>
#include <vector>
#include <memory>
#include "Point.hpp"
#include "GameObject.hpp"

namespace spic {
    enum class FlockBehaviour {
        SEEK,
        FLEE,
        ARRIVAL,
        WANDER
    };

    /**
     * @brief Component which can play audio.
     */
    class Flock : public spic::GameObject {  
    public:
        Flock(const spic::FlockBehaviour flockBehaviour, const float maxSteeringForce, const float maxSpeed);

        Point Velocity();
        float Mass();

        void FlockBehaviour(const spic::FlockBehaviour flockBehaviour);

        void WallAvoidance(const float wallAvoidanceWeight, const float width, const float height);
        void ObstacleAvoidance(const float obstacleAvoidanceWeight, const float feelerTreshold);
        void Seperation(const float seperationWeight, const float desiredSeparation);
        void Alignment(const float alignmentWeight, const float viewRadius);
        void Cohesion(const float cohesionWeight, const float viewRadius);

        void Target(std::unique_ptr<Point> newTarget, const float targetWeight);
        void Target(std::unique_ptr<Point> newTarget);

        void StartFlock();
        void UpdateFlock(const std::vector<std::shared_ptr<Flock>>& flocks);
        void StopFlock();
    private:
        Point Calculate(const std::vector<std::shared_ptr<Flock>>& flocks);

        Point Seek(Point& target);
        Point Flee(Point& target);
        Point Arrival(Point& target);
        Point Wander(Point& target);

        Point WallAvoidance();
        Point ObstacleAvoidance();

        Point Seperate(const std::vector<std::shared_ptr<Flock>>& flocks);
        Point Align(const std::vector<std::shared_ptr<Flock>>& flocks);
        Point Cohere(const std::vector<std::shared_ptr<Flock>>& flocks);

        void ApplyForce(Point& force);
    private:
        spic::FlockBehaviour flockBehaviour;
        float maxSteeringForce;
        float maxSpeed;
        bool paused;

        // Target
        std::unique_ptr<Point> target;
        float targetWeight;

        // Seperation
        float seperationWeight;
        float desiredSeparation;

        // Alignment
        float alignmentWeight;

        // Cohesion
        float cohesionWeight;
        float viewRadius;

        // Wall avoidance
        float wallAvoidanceWeight;
        float width;
        float height;

        // Obstacle avoidance
        // When feeler reaches certain treshold start aplying obstacle avoidance force
        float obstacleAvoidanceWeight;
        float feelerTreshold;

        // Settings using forces
        bool useWallAvoidance;
        bool useObstacleAvoidance;
        bool useSeperation;
        bool useAlignment;
        bool useCohesion;
        bool useTarget;
    };

}

#endif // FLOCK_H_
