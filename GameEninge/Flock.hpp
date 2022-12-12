#ifndef FLOCK_H_
#define FLOCK_H_

#include <string>
#include <vector>
#include <memory>
#include "Point.hpp"
#include "GameObject.hpp"
#include "Bounds.hpp"

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

        Point Velocity() const;
        Point Heading() const;
        float Mass() const;

        void UseSeek();
        void UseFlee();
        void UseArrival(Deceleration deceleration = Deceleration::NORMAL);
        void UseWander(const float wanderRadius = 1.0f, const float wanderDistance = 6.0f, const float wanderJitter = 60.0f);

        void WallAvoidance(const float wallAvoidanceWeight, const float wallDetectionFeelerLength, const Bounds& bounds);
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
        void TagNeighbors(const std::vector<std::shared_ptr<Flock>>& flocks);

        Point Calculate();
        Point CalculateWeightedSum();
        Point CalculatePrioritized();

        Point Seek(Point target);
        Point Flee(Point target);
        Point Arrival(Point target);
        Point Wander();

        Point WallAvoidance();
        Point ObstacleAvoidance();

        Point Seperate();
        Point Align();
        Point Cohere();

        void ApplyForce(Point& force);
    private:
        // General variables
        SumMethod sumMethod;
        spic::FlockBehaviour flockBehaviour;
        float maxSteeringForce;
        float maxSpeed;
        float angleSensitivity; // in rad
        bool paused;
        Point heading;
        std::vector<std::shared_ptr<Flock>> neighbors;

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
        float wallDetectionFeelerLength;
        Bounds bounds;

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
