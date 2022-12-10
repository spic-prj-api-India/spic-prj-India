#ifndef FLOCK_H_
#define FLOCK_H_

#include <string>
#include <vector>
#include <memory>
#include "Point.hpp"
#include "GameObject.hpp"

namespace spic {
    enum class SumMethod { WEIGHTED_AVERAGE, PRIORITIZED };

    enum class FlockBehaviour {
        SEEK,
        FLEE,
        ARRIVAL,
        WANDER
    };

    enum class Deceleration { SLOW = 3, NORMAL = 2, FAST = 1 };

    /**
     * @brief Component which can play audio.
     */
    class Flock : public spic::GameObject {  
    public:
        Flock(SumMethod sumMethod, const float maxSteeringForce, const float maxSpeed, const float angleSensitivity);

        Point Velocity();
        float Mass();

        void Seek();
        void Flee();
        void Arrival(Deceleration deceleration);
        void Wander(const float wanderRadius, const float wanderDistance, const float wanderJitter);

        void WallAvoidance(const float wallAvoidanceWeight, const float width, const float height);
        void ObstacleAvoidance(const float obstacleAvoidanceWeight, const float feelerTreshold);
        void Seperation(const float seperationWeight, const float desiredSeparation);
        void Alignment(const float alignmentWeight, const float viewRadius);
        void Cohesion(const float cohesionWeight, const float viewRadius);

        void Target(const Point& newTarget, const float targetWeight);
        void Target(const Point& newTarget);

        void StartFlock();
        void UpdateFlock(const std::vector<std::shared_ptr<Flock>>& flocks);
        void StopFlock();
    private:
        Point Calculate(const std::vector<std::shared_ptr<Flock>>& flocks);
        Point CalculateWeightedSum(const std::vector<std::shared_ptr<Flock>>& flocks);
        Point CalculatePrioritized(const std::vector<std::shared_ptr<Flock>>& flocks);

        Point Seek(Point target);
        Point Flee(Point target);
        Point Arrival(Point target);
        Point Wander();

        Point WallAvoidance();
        Point ObstacleAvoidance();

        Point Seperate(const std::vector<std::shared_ptr<Flock>>& flocks);
        Point Align(const std::vector<std::shared_ptr<Flock>>& flocks);
        Point Cohere(const std::vector<std::shared_ptr<Flock>>& flocks);

        void ApplyForce(Point& force);
    private:
        SumMethod sumMethod;
        spic::FlockBehaviour flockBehaviour;
        float maxSteeringForce;
        float maxSpeed;
        // in rad
        float angleSensitivity;
        bool paused;

        // Target
        Point target;
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

        // Wander
        float wanderRadius;
        float wanderDistance;
        float wanderJitter;

        // Arrival
        Deceleration deceleration;

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
