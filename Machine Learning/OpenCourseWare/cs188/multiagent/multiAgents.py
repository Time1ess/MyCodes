#!/usr/bin/env python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-09-21 09:14
# Last modified: 2017-09-22 14:41
# Filename: multiAgents.py
# Description:
# multiAgents.py
# --------------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
# 
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).
import math
import random


from util import manhattanDistance
from game import Directions
import random, util

from game import Agent

class ReflexAgent(Agent):
    """
      A reflex agent chooses an action at each choice point by examining
      its alternatives via a state evaluation function.

      The code below is provided as a guide.  You are welcome to change
      it in any way you see fit, so long as you don't touch our method
      headers.
    """


    def getAction(self, gameState):
        """
        You do not need to change this method, but you're welcome to.

        getAction chooses among the best options according to the evaluation function.

        Just like in the previous project, getAction takes a GameState and returns
        some Directions.X for some X in the set {North, South, West, East, Stop}
        """
        # Collect legal moves and successor states
        legalMoves = gameState.getLegalActions()

        # Choose one of the best actions
        scores = [self.evaluationFunction(gameState, action) for action in legalMoves]
        bestScore = max(scores)
        bestIndices = [index for index in range(len(scores)) if scores[index] == bestScore]
        chosenIndex = random.choice(bestIndices) # Pick randomly among the best

        "Add more of your code here if you want to"

        return legalMoves[chosenIndex]

    def evaluationFunction(self, currentGameState, action):
        """
        Design a better evaluation function here.

        The evaluation function takes in the current and proposed successor
        GameStates (pacman.py) and returns a number, where higher numbers are better.

        The code below extracts some useful information from the state, like the
        remaining food (newFood) and Pacman position after moving (newPos).
        newScaredTimes holds the number of moves that each ghost will remain
        scared because of Pacman having eaten a power pellet.

        Print out these variables to see what you're getting, then combine them
        to create a masterful evaluation function.
        """
        # Useful information you can extract from a GameState (pacman.py)
        successorGameState = currentGameState.generatePacmanSuccessor(action)
        newPos = successorGameState.getPacmanPosition()  # (x, y)
        newFood = successorGameState.getFood().asList()  # food[x][y]: true or false
        newGhostStates = successorGameState.getGhostStates()  # [state]
        newScaredTimes = [ghostState.scaredTimer for ghostState in newGhostStates]
        plus_score = 0

        dist_score = 0
        for ghost_state, scare_time in zip(newGhostStates, newScaredTimes):
            x, y = ghost_state.getPosition()
            dist = abs(x - newPos[0]) + abs(y - newPos[1])
            if scare_time > 35:
                dist_score += 10 # Encourage pacman to eat buff
            elif scare_time > 2:  # Encourage pacman to eat ghosts
                dist_score += 0
            else:
                if dist < 3:
                    dist_score -= 10 * (5 - dist)
                elif dist < 6:
                    dist_score -= 1 * (8 - dist)
                else:
                    dist_score += 0.2 * dist
        plus_score += dist_score

        food_score = 1000
        for (x, y) in newFood:
            dist = abs(x - newPos[0]) + abs(y - newPos[1])
            food_score = min(food_score, -dist)
        plus_score += food_score
        score = successorGameState.getScore() + plus_score
        return score

def scoreEvaluationFunction(currentGameState):
    """
      This default evaluation function just returns the score of the state.
      The score is the same one displayed in the Pacman GUI.

      This evaluation function is meant for use with adversarial search agents
      (not reflex agents).
    """
    return currentGameState.getScore()

class MultiAgentSearchAgent(Agent):
    """
      This class provides some common elements to all of your
      multi-agent searchers.  Any methods defined here will be available
      to the MinimaxPacmanAgent, AlphaBetaPacmanAgent & ExpectimaxPacmanAgent.

      You *do not* need to make any changes here, but you can if you want to
      add functionality to all your adversarial search agents.  Please do not
      remove anything, however.

      Note: this is an abstract class: one that should not be instantiated.  It's
      only partially specified, and designed to be extended.  Agent (game.py)
      is another abstract class.
    """

    def __init__(self, evalFn = 'scoreEvaluationFunction', depth = '2'):
        self.index = 0 # Pacman is always agent index 0
        self.evaluationFunction = util.lookup(evalFn, globals())
        self.depth = int(depth)

class MinimaxAgent(MultiAgentSearchAgent):
    """
      Your minimax agent (question 2)
    """

    def getAction(self, gameState):
        """
          Returns the minimax action from the current gameState using self.depth
          and self.evaluationFunction.

          Here are some method calls that might be useful when implementing minimax.

          gameState.getLegalActions(agentIndex):
            Returns a list of legal actions for an agent
            agentIndex=0 means Pacman, ghosts are >= 1

          gameState.generateSuccessor(agentIndex, action):
            Returns the successor game state after an agent takes an action

          gameState.getNumAgents():
            Returns the total number of agents in the game
        """
        def value(state, depth, agent):
            if agent == state.getNumAgents():
                if depth == self.depth:
                    return self.evaluationFunction(state)
                else:
                    return value(state, depth+1, 0)
            else:
                actions = state.getLegalActions(agent)
                if len(actions) == 0:
                    return self.evaluationFunction(state)
                successors = (value(state.generateSuccessor(agent, action),
                                    depth, agent+1) for action in actions)
                return (max if agent == 0 else min)(successors)

        return max(
            gameState.getLegalActions(0),
            key=lambda x: value(gameState.generateSuccessor(0, x), 1, 1))



class AlphaBetaAgent(MultiAgentSearchAgent):
    """
      Your minimax agent with alpha-beta pruning (question 3)
    """

    def getAction(self, gameState):
        """
          Returns the minimax action using self.depth and self.evaluationFunction
        """
        def value(state, depth, agent, alpha, beta):
            if agent == state.getNumAgents():
                if depth == self.depth:
                    return self.evaluationFunction(state)
                else:
                    return value(state, depth+1, 0, alpha, beta)
            else:
                actions = state.getLegalActions(agent)
                if len(actions) == 0:
                    return self.evaluationFunction(state)
                if agent == 0:  # Max-node
                    v = -1e9
                    for action in actions:
                        v = max(v,
                                value(state.generateSuccessor(agent, action),
                                      depth, agent+1, alpha, beta))
                        if v > beta:
                        # This node will be skipped due to final value >= v
                        # but parent node already can get at most beta
                            return v
                        alpha = max(alpha, v)
                else:  # Min-node
                    v = 1e9
                    for action in actions:
                        v = min(v, value(state.generateSuccessor(agent, action),
                                         depth, agent+1, alpha, beta))
                        if v < alpha:
                        # This node will be skipped due to final value <= v 
                        # but parent node already can get at least alpha
                            return v
                        beta = min(beta, v)
                return v

        actions = gameState.getLegalActions(0)
        best_action = None
        alpha, beta = -1e9, 1e9
        for action in actions:
            v = value(gameState.generateSuccessor(0, action),
                      1, 1, alpha, beta)
            if v > alpha or best_action is None:
                alpha = v
                best_action = action
        return best_action


class ExpectimaxAgent(MultiAgentSearchAgent):
    """
      Your expectimax agent (question 4)
    """

    def getAction(self, gameState):
        """
          Returns the expectimax action using self.depth and self.evaluationFunction

          All ghosts should be modeled as choosing uniformly at random from their
          legal moves.
        """
        def average(values):
            values = list(values)
            return sum(values) / len(values)

        def value(state, depth, agent):
            if agent == state.getNumAgents():
                if depth == self.depth:
                    return self.evaluationFunction(state)
                else:
                    return value(state, depth+1, 0)
            else:
                actions = state.getLegalActions(agent)
                if len(actions) == 0:
                    return self.evaluationFunction(state)
                successors = (value(state.generateSuccessor(agent, action),
                                    depth, agent+1) for action in actions)
                return (max if agent == 0 else average)(successors)

        return max(
            gameState.getLegalActions(0),
            key=lambda x: value(gameState.generateSuccessor(0, x), 1, 1))


class Directions:
    NORTH = 'North'
    SOUTH = 'South'
    EAST = 'East'
    WEST = 'West'
    STOP = 'Stop'

    LEFT =       {NORTH: WEST,
                   SOUTH: EAST,
                   EAST:  NORTH,
                   WEST:  SOUTH,
                   STOP:  STOP}

    RIGHT =      dict([(y,x) for x, y in LEFT.items()])

    REVERSE = {NORTH: SOUTH,
               SOUTH: NORTH,
               EAST: WEST,
               WEST: EAST,
               STOP: STOP}


class Actions:
    """
    A collection of static methods for manipulating move actions.
    """
    # Directions
    _directions = {Directions.NORTH: (0, 1),
                   Directions.SOUTH: (0, -1),
                   Directions.EAST:  (1, 0),
                   Directions.WEST:  (-1, 0),
                   Directions.STOP:  (0, 0)}

    _directionsAsList = _directions.items()

    TOLERANCE = .001

    def reverseDirection(action):
        if action == Directions.NORTH:
            return Directions.SOUTH
        if action == Directions.SOUTH:
            return Directions.NORTH
        if action == Directions.EAST:
            return Directions.WEST
        if action == Directions.WEST:
            return Directions.EAST
        return action
    reverseDirection = staticmethod(reverseDirection)

    def vectorToDirection(vector):
        dx, dy = vector
        if dy > 0:
            return Directions.NORTH
        if dy < 0:
            return Directions.SOUTH
        if dx < 0:
            return Directions.WEST
        if dx > 0:
            return Directions.EAST
        return Directions.STOP
    vectorToDirection = staticmethod(vectorToDirection)

    def directionToVector(direction, speed = 1.0):
        dx, dy =  Actions._directions[direction]
        return (dx * speed, dy * speed)
    directionToVector = staticmethod(directionToVector)

    def getPossibleActions(config, walls):
        possible = []
        x, y = config.pos
        x_int, y_int = int(x + 0.5), int(y + 0.5)

        # In between grid points, all agents must continue straight
        if (abs(x - x_int) + abs(y - y_int)  > Actions.TOLERANCE):
            return [config.getDirection()]

        for dir, vec in Actions._directionsAsList:
            dx, dy = vec
            next_y = y_int + dy
            next_x = x_int + dx
            if not walls[next_x][next_y]: possible.append(dir)

        return possible

    getPossibleActions = staticmethod(getPossibleActions)

    def getLegalNeighbors(position, walls):
        x,y = position
        x_int, y_int = int(x + 0.5), int(y + 0.5)
        neighbors = []
        for dir, vec in Actions._directionsAsList:
            dx, dy = vec
            next_x = x_int + dx
            if next_x < 0 or next_x == walls.width: continue
            next_y = y_int + dy
            if next_y < 0 or next_y == walls.height: continue
            if not walls[next_x][next_y]: neighbors.append((next_x, next_y))
        return neighbors
    getLegalNeighbors = staticmethod(getLegalNeighbors)

    def getSuccessor(position, action):
        dx, dy = Actions.directionToVector(action)
        x, y = position
        return (x + dx, y + dy)
    getSuccessor = staticmethod(getSuccessor)


class PositionSearchProblem(object):
    """
    A search problem defines the state space, start state, goal test, successor
    function and cost function.  This search problem can be used to find paths
    to a particular point on the pacman board.

    The state space consists of (x,y) positions in a pacman game.

    Note: this search problem is fully specified; you should NOT change it.
    """

    def __init__(self, gameState, costFn = lambda x: 1, goal=(1,1), start=None, warn=True, visualize=True):
        """
        Stores the start and goal.

        gameState: A GameState object (pacman.py)
        costFn: A function from a search state (tuple) to a non-negative number
        goal: A position in the gameState
        """
        self.walls = gameState.getWalls()
        self.startState = gameState.getPacmanPosition()
        if start != None: self.startState = start
        self.goal = goal
        self.costFn = costFn
        self.visualize = visualize
        if warn and (gameState.getNumFood() != 1 or not gameState.hasFood(*goal)):
            print 'Warning: this does not look like a regular search maze'

        # For display purposes
        self._visited, self._visitedlist, self._expanded = {}, [], 0 # DO NOT CHANGE

    def getStartState(self):
        return self.startState

    def isGoalState(self, state):
        isGoal = state == self.goal

        # For display purposes only
        if isGoal and self.visualize:
            self._visitedlist.append(state)
            import __main__
            if '_display' in dir(__main__):
                if 'drawExpandedCells' in dir(__main__._display): #@UndefinedVariable
                    __main__._display.drawExpandedCells(self._visitedlist) #@UndefinedVariable

        return isGoal

    def getSuccessors(self, state):
        """
        Returns successor states, the actions they require, and a cost of 1.

         As noted in search.py:
             For a given state, this should return a list of triples,
         (successor, action, stepCost), where 'successor' is a
         successor to the current state, 'action' is the action
         required to get there, and 'stepCost' is the incremental
         cost of expanding to that successor
        """

        successors = []
        for action in [Directions.NORTH, Directions.SOUTH, Directions.EAST, Directions.WEST]:
            x,y = state
            dx, dy = Actions.directionToVector(action)
            nextx, nexty = int(x + dx), int(y + dy)
            if not self.walls[nextx][nexty]:
                nextState = (nextx, nexty)
                cost = self.costFn(nextState)
                successors.append( ( nextState, action, cost) )

        # Bookkeeping for display purposes
        self._expanded += 1 # DO NOT CHANGE
        if state not in self._visited:
            self._visited[state] = True
            self._visitedlist.append(state)

        return successors

    def getCostOfActions(self, actions):
        """
        Returns the cost of a particular sequence of actions. If those actions
        include an illegal move, return 999999.
        """
        if actions == None: return 999999
        x,y= self.getStartState()
        cost = 0
        for action in actions:
            # Check figure out the next state and see whether its' legal
            dx, dy = Actions.directionToVector(action)
            x, y = int(x + dx), int(y + dy)
            if self.walls[x][y]: return 999999
            cost += self.costFn((x,y))
        return cost


class AnyFoodSearchProblem(PositionSearchProblem):
    """
    A search problem for finding a path to any food.

    This search problem is just like the PositionSearchProblem, but has a
    different goal test, which you need to fill in below.  The state space and
    successor function do not need to be changed.

    The class definition above, AnyFoodSearchProblem(PositionSearchProblem),
    inherits the methods of the PositionSearchProblem.

    You can use this search problem to help you fill in the findPathToClosestDot
    method.
    """

    def __init__(self, gameState):
        "Stores information from the gameState.  You don't need to change this."
        # Store the food for later reference
        self.food = gameState.getFood()

        # Store info for the PositionSearchProblem (no need to change this)
        self.walls = gameState.getWalls()
        self.startState = gameState.getPacmanPosition()
        self.costFn = lambda x: 1
        self._visited, self._visitedlist, self._expanded = {}, [], 0 # DO NOT CHANGE

    def isGoalState(self, state):
        """
        The state is Pacman's position. Fill this in with a goal test that will
        complete the problem definition.
        """
        x,y = state

        return self.food[x][y] is True


def aStarSearch(problem, heuristic):
    """Search the node that has the lowest combined cost and heuristic first."""
    pq = util.PriorityQueue()
    src_state = problem.getStartState()
    g = 0
    h = heuristic(src_state, problem)
    pq.push((src_state, g, h, []), g+h)
    states = set()
    while not pq.isEmpty():
        src_state, src_g, src_h, actions = pq.pop()
        if src_state in states:
            continue
        states.add(src_state)
        if problem.isGoalState(src_state):
            return actions
        for dst_state, direction, cost in problem.getSuccessors(src_state):
            dst_actions = [a for a in actions]
            dst_actions.append(direction)
            dst_g = src_g + cost
            dst_h = heuristic(dst_state, problem)
            pq.push((dst_state, dst_g, dst_h, dst_actions), dst_g + dst_h)
    return []


def manhattan_distance(p1, p2):
    return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1])


def nearest_food_heuristic(pos, problem):
    food = problem.food.asList()
    dists = [manhattan_distance(pos, food_pos) for food_pos in food]
    return min(dists) if dists else 0


def betterEvaluationFunction(currentGameState):
    """
      Your extreme ghost-hunting, pellet-nabbing, food-gobbling, unstoppable
      evaluation function (question 5).

      DESCRIPTION: <write something here so we know what you did>
    """
    pos = currentGameState.getPacmanPosition()
    food = currentGameState.getFood().asList()
    ghosts = currentGameState.getGhostStates()
    scared = [ghost for ghost in ghosts if ghost.scaredTimer > 0]
    ghosts = [ghost for ghost in ghosts if ghost.scaredTimer == 0]
    capsules = currentGameState.getCapsules()

    food_left = len(food)
    capsule_left = len(capsules)

    # Food
    problem = AnyFoodSearchProblem(currentGameState)
    shortest_food = aStarSearch(problem, nearest_food_heuristic)
    food_score = 1.0 / len(shortest_food) if shortest_food else 1000

    # Ghosts
    if ghosts:
        dists = [manhattan_distance(pos, ghost.getPosition()) for ghost in
                 ghosts]
        min_dist = min(dists)
        ghost_score = 20000 if min_dist == 0 else 1.0 / min_dist
    else:
        ghost_score = 0

    # Scared ghosts
    scared_score = 0
    if scared:
        dists = [manhattan_distance(pos, ghost.getPosition()) for ghost in
                 scared]
        dists = [dist for ghost, dist in zip(scared, dists)
                 if dist <= ghost.scaredTimer]
        if dists:
            min_dist = min(dists)
            scared_score = 100 if min_dist == 0 else 1.0 / min_dist

    # Capsules
    if capsules:
        dists = [manhattan_distance(pos, cap) for cap in
                 capsules]
        min_dist = min(dists)
        capsule_score = 1.0 / min_dist
    else:
        capsule_score = 0

    weights = [-5, -20, 5, -10, 40, 10]
    scores = [food_left, capsule_left, food_score,
              ghost_score, scared_score, capsule_score]
    scores = [i * j for i, j in zip(weights, scores)]
    score = sum(scores)
    return score

# Abbreviation
better = betterEvaluationFunction

