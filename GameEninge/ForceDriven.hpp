#ifndef FORCEDRIVEN_H_
#define FORCEDRIVEN_H_

#include <string>
#include <vector>
#include <memory>
#include "Point.hpp"
#include "GameObject.hpp"
#include "Bounds.hpp"
#include <map>
#include <functional>

namespace spic {
    /**
     * @brief WEIGHTED_AVERAGE Adds all forces anf gets average force. 
     *              PRIORITIZED Adds forces forces until max force is reached.
     * @spicapi
     */
    enum class SumMethod { WEIGHTED_AVERAGE, PRIORITIZED };

    enum class SteeringBehaviour {
        SEEK,
        FLEE,
        ARRIVAL,
        WANDER
    };

    /**
     * @brief Deceleration of force driven entity, is used for arrival behaviour.
     * @spicapi
     */
    enum class Deceleration { SLOW = 3, NORMAL = 2, FAST = 1 };

    /**
     * @brief Force driven entity only moves with force.
     */
    class ForceDriven : public spic::GameObject {  
    public:
        ForceDriven(SumMethod sumMethod, const float maxSteeringForce, const float maxSpeed, const float angleSensitivity);

        /**
         * @brief Returns velocity of force driven entity.
         * @return spic::Point.
         * @spicapi
        */
        Point Velocity() const;

        /**
         * @brief Returns direction that force driven entity is going to.
         * @return spic::Point.
         * @spicapi
        */
        Point Heading() const;

        /**
         * @brief Returns mass of force driven entity.
         * @return float.
         * @spicapi
        */
        float Mass() const;

        /**
         * @brief Adds target with targetWeight for specific SteeringBehaviour.
         * @param steeringBehaviour SteeringBehaviour that is used for target.
         * @param target Desired target.
         * @param targetWeight Weight that shows how much target steering behaviour influences the steering force.
         * @spicapi
        */
        void AddTarget(SteeringBehaviour steeringBehaviour, Point& target, const float targetWeight);

        /**
         * @brief Removes target for specific SteeringBehaviour.
         * @param steeringBehaviour SteeringBehaviour that is used for target.
         * @param target Desired target to remove.
         * @spicapi
        */
        void RemoveTarget(SteeringBehaviour steeringBehaviour, Point& target);

        /**
         * @brief Removes steering behaviour and all underlying targets.
         * @param steeringBehaviour SteeringBehaviour to remove.
         * @spicapi
        */
        void RemoveSteeringBehaviour(SteeringBehaviour steeringBehaviour);

        /**
         * @brief Sets steering behaviour to SEEK.
         * @param targets Targets to seek to.
         * @spicapi
        */
        void UseSeek(std::map<std::reference_wrapper<Point>, float, std::less<Point>> targets);

        /**
         * @brief Sets steering behaviour to FLEE.
         * @param targets Targets to flee from.
         * @spicapi
        */
        void UseFlee(std::map<std::reference_wrapper<Point>, float, std::less<Point>> targets);

        /**
         * @brief Sets steering behaviour to ARRIVAL.
         * @param deceleration Deceleration that is used when force driven entity arrives at target.
         * @param targets Targets to arrive at.
         * @spicapi
        */
        void UseArrival(std::map<std::reference_wrapper<Point>, float, std::less<Point>> targets, 
            Deceleration deceleration = Deceleration::NORMAL);

        /**
         * @brief Sets steering behaviour to WANDER.
         * @param wanderRadius The radius of the constraining circle for the wander behaviour.
         * @param wanderDistance The distance the wander circle is projected in front of the agent.
         * @param wanderJitter The maximum amount of displacement along the circle each frame.
         * @spicapi
        */
        void UseWander(const float wanderWeight, const float wanderRadius = 1.0f, const float wanderDistance = 6.0f, const float wanderJitter = 60.0f);

        /**
        * @brief Activates wall avoidance for force driven entity.
        * @param wallAvoidanceWeight The weight of the behaviour.
        * @param wallDetectionFeelerLength The length of the 3 feelers that are attached to the front of the force driven entity.
        * @param bounds The bounds were the force driven entity needs to be kept in.
        * @spicapi
        */
        void WallAvoidance(const float wallAvoidanceWeight, const float wallDetectionFeelerLength, const Bounds& bounds);
        
        /**
         * @brief Activates obstacle avoidance for force driven entity.
         * @param obstacleAvoidanceWeight The weight of the behaviour.
         * @param feelerLength The length of the 3 feelers that are attached to the front of the force driven entity.
         * @spicapi
        */
        void ObstacleAvoidance(const float obstacleAvoidanceWeight, const float feelerLength);

        /**
         * @brief Activates seperation for force driven entity
         * @param seperationWeight The weight of the behaviour.
         * @param desiredSeparation The desperation space between force driven entities.
         * @spicapi
        */
        void Seperation(const float seperationWeight, const float desiredSeparation);

        /**
         * @brief Activates alignment for force driven entity.
         * @param alignmentWeight The weight of the behaviour.
         * @param viewRadius The radius where the entity searches for neighbors.
         * @spicapi
        */
        void Alignment(const float alignmentWeight, const float viewRadius);

        /**
         * @brief Activates cohesion for force driven entity.
         * @param cohesionWeight The weight of the behaviour.
         * @param viewRadius The radius where the entity searches for neighbors.
         * @spicapi
        */
        void Cohesion(const float cohesionWeight, const float viewRadius);

        /**
         * @brief Activates new target.
         * @param newTarget The desired target point.
         * @param targetWeight The weight of the target.
         * @spicapi
        */
        void Target(const Point& newTarget, const float targetWeight);

        /**
         * @brief Activates new target.
         * @param newTarget The desired target point.
         * @spicapi
        */
        void Target(const Point& newTarget);

        /**
         * @brief Starts force driven entity if steering behaviour is defined.
         * @param newTarget The desired target point.
         * @param targetWeight The weight of the target.
         * @spicapi
        */
        void StartForceDrivenEntity();

        /**
        * @brief Updates force driven entity.
        * @param forceDrivenEntities The list of all force driven entities that are active.
        * @spicapi
        */
        void UpdateForceDrivenEntity(const std::vector<std::shared_ptr<ForceDriven>>& forceDrivenEntities);

        /**
        * @brief Stops force driven entity.
        * @spicapi
        */
        void StopForceDrivenEntity();
    private:
        /**
        * @brief Tags all nearby neigbors.
        * @param forceDrivenEntities The list of all force driven entities that are active.
        * @spicapi
        */
        void TagNeighbors(const std::vector<std::shared_ptr<ForceDriven>>& forceDrivenEntities);

        /**
        * @brief Calculates steering force.
        * @return spic::Point Steering force.
        * @spicapi
        */
        Point Calculate();

        /**
         * @brief Calculates steering force with weighed sum method.
         * @return spic::Point Steering force.
         * @spicapi
        */
        Point CalculateWeightedSum();

        /**
         * @brief Calculates steering force with prioritized sum method.
         * @return spic::Point Steering force.
         * @spicapi
        */
        Point CalculatePrioritized();

        /**
         * @brief Add all steering forces to steering force.
         * @param addSteeringForceCallback Callback that adds forces to steering force.
         * @spicapi
        */
        void AddSteeringForces(std::function<bool(Point force)> addSteeringForceCallback);

        /**
         * @brief Seek to target and return steering force.
         * @return spic::Point Steering force.
         * @spicapi
        */
        Point Seek(Point target);

        /**
        * @brief Flee from target and return steering force.
        * @return spic::Point Steering force.
        * @spicapi
        */
        Point Flee(Point target);

        /**
        * @brief Arrive at target and return steering force.
        * @return spic::Point Steering force.
        * @spicapi
        */
        Point Arrival(Point target);

        /**
        * @brief Wander randomly around scene and return steering force.
        * @return spic::Point Steering force.
        * @spicapi
        */
        Point Wander();

        /**
        * @brief Calculates steering force to avoid walls.
        * @return spic::Point Steering force.
        * @spicapi
        */
        Point WallAvoidance();

        /**
        * @brief Calculates steering force to avoid obstacles.
        * @return spic::Point Steering force.
        * @spicapi
        */
        Point ObstacleAvoidance();

        /**
        * @brief Calculates steering force to seperate from force driven entities.
        * @return spic::Point Steering force.
        * @spicapi
        */
        Point Seperate();

        /**
        * @brief Calculates steering force to align force driven entities.
        * @return spic::Point Steering force.
        * @spicapi
        */
        Point Align();

        /**
        * @brief Calculates steering force to cohere force driven entities together.
        * @return spic::Point Steering force.
        * @spicapi
        */
        Point Cohere();

        void ApplyForce(Point& force);
    private:
        /**
        * @brief Default properties.
        */
        SumMethod sumMethod;
        float maxSteeringForce;
        float maxSpeed;
        float angleSensitivity; // in rad
        bool paused;
        Point heading;
        std::vector<std::shared_ptr<ForceDriven>> neighbors;

        /**
        * @brief Target properties.
        *       Every steering force has a map with a target as a key and a target weight as value.
        */
        std::map<spic::SteeringBehaviour, std::map<std::reference_wrapper<Point>, float, std::less<Point>>> steeringBehavioursIncludingTargets;

        /**
        * @brief Seperation properties.
        */
        float seperationWeight;
        float desiredSeparation;

        /**
        * @brief Alignment properties.
        */
        float alignmentWeight;

        /**
        * @brief Cohesion properties.
        */
        float cohesionWeight;
        float viewRadius;

        /**
        * @brief Wall avoidance properties.
        */
        float wallAvoidanceWeight;
        float wallDetectionFeelerLength;
        Bounds bounds;

        /**
        * @brief Obstacle avoidance properties. 
                When feeler reaches certain treshold start aplying obstacle avoidance force
        */
        float obstacleAvoidanceWeight;
        float feelerLength;

        /**
        * @brief Wander properties.
        */
        float wanderWeight;
        float wanderRadius;
        float wanderDistance;
        float wanderJitter;

        /**
        * @brief Arrival properties.
        */
        Deceleration deceleration;

        /**
        * @brief Using forces properties.
        */
        bool useWallAvoidance;
        bool useObstacleAvoidance;
        bool useSeperation;
        bool useAlignment;
        bool useCohesion;
        bool useTarget;
    };
}

#endif // FORCEDRIVEN_H_
