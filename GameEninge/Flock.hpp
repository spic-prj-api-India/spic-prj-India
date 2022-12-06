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
        Flock(const spic::FlockBehaviour flockBehaviour, const std::shared_ptr<spic::GameObject> target, const float maxSteeringForce,
            const float maxSpeed, const float flockBehaviourWeight);

        void FlockBehaviour(const spic::FlockBehaviour flockBehaviour);

        void WallAvoidance(const float wallAvoidanceWeight, const float width, const float height);
        void ObstacleAvoidance(const float obstacleAvoidanceWeight, const float feelerTreshold);
        void Seperation(const float seperationWeight);
        void Alignment(const float alignmentWeight);
        void Cohesion(const float cohesionWeight);

        void Target(const std::shared_ptr<spic::GameObject> target);

        void StartFlock();
        void UpdateFlock(const std::vector<std::shared_ptr<Flock>>& flocks);
        void StopFlock();
    private:
        Point Calculate(const std::vector<std::shared_ptr<Flock>>& flocks);

        Point Seek();
        Point Flee();
        Point Arrival();
        Point Wander();

        Point WallAvoidance();
        Point ObstacleAvoidance();

        Point Seperate(const std::vector<std::shared_ptr<Flock>>& flocks);
        Point Align(const std::vector<std::shared_ptr<Flock>>& flocks);
        Point Cohere(const std::vector<std::shared_ptr<Flock>>& flocks);

        void ApplyForce(const Point& force);
    private:
        std::shared_ptr<spic::GameObject> target;
        spic::FlockBehaviour flockBehaviour;
        float flockBehaviourWeight;
        float maxSteeringForce;
        float maxSpeed;
        bool paused;

        // Seperation
        float seperationWeight;

        // Alignment
        float alignmentWeight;

        // Cohesion
        float cohesionWeight;

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
    };

}

#endif // FLOCK_H_
