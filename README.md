# Neural Network Library

## Overview

This project is a neural network library written in C++.
The primary goal of this library is to explore the workings of neural networks and computer algebra libraries. 

## Features

The library currently includes the following main components:

1. **Activation Functions**  
   - **Sigmoid**  
   - **Tanh**  
   - **Softplus**  
   - **Linear**  
   - **Max**  
   - **Average**  

2. **Fully Connected Layer**  
   *Layer can be created with constructors: __FCNetwork( Weights, ActivationFunction)__*

3. **Learning Algorithms**  
   Currently, the library implements one learning algorithm:
   - **Stochastic Gradient Descent (SGD)**  
To train the neural network, it is necessary to create a trainer.
   - *__Trainer(coefficients, MethodOpts)__*
The trainer must be passed to the *__train(input, error, trainer)__* function of FCNNetwork,
along with the error matrix and the vector of input values.

## Neural Network Functions

The library provides the following core functionalities for neural networks:

- **Forward Propagation**  
  *__forward(input)__*

- **Backward Propagation**  
  *__backword(error)__*

- **Training**  
  *__train(input, error, trainer)__*

## Installation

It was tested only with __armadillo11__ library version __1.11__

## Important
__"This library is in the early stages of development."__
