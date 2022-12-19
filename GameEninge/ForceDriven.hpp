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

    /**
     * @brief Force driven entity only moves with force.
     */
    class ForceDriven : public spic::GameObject {  
    public:
        ForceDriven(SumMethod sumMethod, const float maxSteeringForce, const float maxSpeed, const float maxTurnRate, const float boundingRadius);

        /**
         * @brief Returns velocity of force driven entity.
         * @return spic::Point.
         * @spicapi
        */
        Point Velocity() const;

        /**
         * @brief Returns max speed of force driven entity.
         * @return spic::Point.
         * @spicapi
        */
        float MaxSpeed() const;

        /**
         * @brief Returns direction that force driven entity is going to.
         * @return spic::Point.
         * @spicapi
        */
        Point Heading() const;

        /**
         * @brief Returns vector perpendicular to heading.
         * @return spic::Point.
         * @spicapi
        */
        Point Side() const;

        /**
         * @brief Returns mass of force driven entity.
         * @return float.
         * @spicapi
        */
        float Mass() const;

        /**
         * @brief Returns bounding radius of force driven entity.
         * @return float.
         * @spicapi
        */
        float BRadius() const;

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
         * @brief Applies steering force to force driven entity.
         * @param spic::Point Steering force.
         * @spicapi
        */
        void ApplyForce(Point& force);
    private:
        /**
        * @brief Default properties.
        */
        SumMethod sumMethod;
        float maxSteeringForce;
        float maxSpeed;
        float maxTurnRate; // in rad
        bool paused;
        Point heading;
        float boundingRadius;
    };
}

#endif // FORCEDRIVEN_H_
