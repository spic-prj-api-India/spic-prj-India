#ifndef PATHFINDING_H_
#define PATHFINDING_H_

#include "Component.hpp"
#include <string>
#include <vector>
#include <memory>
#include "Point.hpp"

namespace spic {
    /**
     * @brief Component which can play audio.
     */
    class Pathfinding : public Component {  
    public:
        Pathfinding(const std::shared_ptr<spic::GameObject> target, const float pathFindingWeight,
            const float obstacleAvoidanceWeight, const float feelerTreshold);

        void Target(const std::shared_ptr<spic::GameObject> target);
        void PathFindingWeight(const int newPathFindingWeight);
        void ObstacleAvoidanceWeight(const int newObstacleAvoidanceWeight);
        void FeelerTreshold(const int newFeelerTreshold);

        void Start();
        void Update();
        void Stop();
    private:
        Point Path();
        Point ObstacleAvoidance();
        void ApplyForce(const Point& force);
    private:
        std::shared_ptr<spic::GameObject> target;
        /// <summary>
        /// Weight for path finding
        /// </summary>
        float pathFindingWeight;
        /// <summary>
        /// Weight for obstacle avoidance
        /// </summary>
        float obstacleAvoidanceWeight;
        /// <summary>
        /// When feeler reaches certain treshold start aplying obstacle avoidance force
        /// </summary>
        float feelerTreshold;
        bool paused;
    };

}

#endif // PATHFINDING_H_
