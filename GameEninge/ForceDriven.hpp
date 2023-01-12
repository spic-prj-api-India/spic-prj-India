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
     */
    enum class SumMethod { WEIGHTED_AVERAGE, PRIORITIZED };

    /**
     * @brief Force driven entity only moves with force.
     */
    class ForceDriven : public spic::GameObject {  
    public:
        /**
         * @brief Constructor
         * @param sumMethod SumMethod is method for summing forces
         * @param maxSteeringForce Max steering force
         * @param maxSpeed Max speed of force driven entity
         * @param maxTurnRate Max angle that force driven entity can turn in radians
         * @param boundingRadius Bounding radius is radius of the bounds around force driven entity. 
                    Is used for collision avoidance.
        */
        ForceDriven(SumMethod sumMethod, const float maxSteeringForce, const float maxSpeed, const float maxTurnRate, const float boundingRadius);

        /**
         * @brief Returns velocity of force driven entity.
         * @return spic::Point.
        */
        Point Velocity() const;

        /**
         * @brief Returns max speed of force driven entity.
         * @return spic::Point.
        */
        float MaxSpeed() const;

        /**
         * @brief Returns direction that force driven entity is going to.
         * @return spic::Point.
        */
        Point Heading() const;

        /**
         * @brief Returns vector perpendicular to heading.
         * @return spic::Point.
        */
        Point Side() const;

        /**
         * @brief Returns mass of force driven entity.
         * @return float.
        */
        float Mass() const;

        /**
         * @brief Returns bounding radius of force driven entity.
         * @return float.
        */
        float BRadius() const;

        /**
         * @brief Starts force driven entity if steering behaviour is defined.
         * @param newTarget The desired target point.
         * @param targetWeight The weight of the target.
        */
        void StartForceDrivenEntity();

        /**
        * @brief Updates force driven entity.
        * @param forceDrivenEntities The list of all force driven entities that are active.
        */
        void UpdateForceDrivenEntity(const std::vector<std::shared_ptr<ForceDriven>>& forceDrivenEntities);

        /**
        * @brief Stops force driven entity.
        */
        void StopForceDrivenEntity();
    private:
        /**
        * @brief Calculates steering force.
        * @return spic::Point Steering force.
        */
        Point Calculate();

        /**
         * @brief Calculates steering force with weighed sum method.
         * @return spic::Point Steering force.
        */
        Point CalculateWeightedSum();

        /**
         * @brief Calculates steering force with prioritized sum method.
         * @return spic::Point Steering force.
        */
        Point CalculatePrioritized();

        /**
         * @brief Applies steering force to force driven entity.
         * @param spic::Point Steering force.
        */
        void ApplyForce(Point& force);

        bool RotateHeadingToFacePosition(Point& force);

        bool RotateHeadingByAngle(float angle, Point& force);
    private:
        /**
        * @brief SumMethod is method for summing forces.
        */
        SumMethod sumMethod;

        /**
         * @brief Max steering force that can be added to force driven entity.
        */
        float maxSteeringForce;

        /**
         * @brief Max speed of entity.
        */
        float maxSpeed;

        /**
         * @brief Max angle that entity can turn in radians.
        */
        float maxTurnRate;

        /**
         * @brief Vector entity is heading towards
        */
        Point heading;

        /**
         * @brief Bounding radius is the radius of the bounds around entity.
                    Bouding radius is used for obstacle avoidance
        */
        float boundingRadius;

        /**
         * @brief Bool if forces need to be added to entity.
        */
        bool paused;
    };
}

#endif // FORCEDRIVEN_H_
