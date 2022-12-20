#ifndef FLOCKING_H_
#define FLOCKING_H_

#include "Component.hpp"
#include <functional>
#include "ForceDriven.hpp"

namespace spic
{
    /**
     * @brief The flocking component is used for implementing flocking for a force driven entity
     */
    class Flocking : public Component {
    public:
        /**
         * @brief Constructor
         * @param agent Agent used for flocking
        */
        Flocking(ForceDriven* agent);

        /**
         * @brief Constructor
         * @param agent Agent used for flocking
         * @param viewRadius The radius where the agent searches for neighbors.
         * @param seperationWeight Weight that is used to calculate impact of seperation
         * @param desiredSeparation Desired separation between agents
         * @param alignmentWeight Weight that is used to calculate impact of alignment
         * @param cohesionWeight Weight that is used to calculate impact of cohesion
        */
        Flocking(ForceDriven* agent, const float viewRadius, const  float seperationWeight, const float desiredSeparation,
            const float alignmentWeight, const float cohesionWeight);

        /**
         * @brief Activates seperation for force driven entity
         * @param seperationWeight The weight of the behaviour.
         * @param desiredSeparation The desperation space between force driven entities.
        */
        void SeperationOn(const float seperationWeight, const float desiredSeparation);

        /**
         * @brief Activates alignment for force driven entity.
         * @param alignmentWeight The weight of the behaviour.
         * @param viewRadius The radius where the agent searches for neighbors.
        */
        void AlignmentOn(const float alignmentWeight, const float viewRadius);

        /**
         * @brief Activates cohesion for force driven entity.
         * @param cohesionWeight The weight of the behaviour.
         * @param viewRadius The radius where the agent searches for neighbors.
        */
        void CohesionOn(const float cohesionWeight, const float viewRadius);

        /**
        * @brief Tags all nearby neigbors.
        * @param forceDrivenEntities The list of all force driven entities that are active.
        */
        void TagNeighbors(const std::vector<std::shared_ptr<ForceDriven>>& forceDrivenEntities);

        /**
        * @brief Calculates steering force.
        * @param addSteeringForceCallback Callback that adds forces to steering force.
        */
        void Calculate(std::function<bool(Point force)> addSteeringForceCallback);
    private:
        /**
       * @brief Calculates steering force to seperate from force driven entities.
       * @return spic::Point Steering force.
       */
        Point Seperate();

        /**
        * @brief Calculates steering force to align force driven entities.
        * @return spic::Point Steering force.
        */
        Point Align();

        /**
         * @brief Seek to target and return steering force.
         * @return spic::Point Steering force.
        */
        Point Seek(Point target);

        /**
        * @brief Calculates steering force to cohere force driven entities together.
        * @return spic::Point Steering force.
        */
        Point Cohere();
    private:
        /**
         * @brief agent used for flocking
        */
        const ForceDriven* agent;

        /**
         * @brief Neigbors of agent
        */
        std::vector<std::shared_ptr<ForceDriven>> neighbors;

        /**
         * @brief The radius where the agent searches for neighbors.
        */
        float viewRadius;

        /**
        * @brief Seperation properties.
        */
        bool useSeperation;
        float seperationWeight;
        float desiredSeparation;

        /**
        * @brief Alignment properties.
        */
        bool useAlignment;
        float alignmentWeight;

        /**
        * @brief Cohesion properties.
        */
        bool useCohesion;
        float cohesionWeight;
    };
}

#endif // FLOCKING_H_