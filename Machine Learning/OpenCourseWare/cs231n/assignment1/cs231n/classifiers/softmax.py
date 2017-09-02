import numpy as np
from random import shuffle
from past.builtins import xrange

def softmax_loss_naive(W, X, y, reg):
  """
  Softmax loss function, naive implementation (with loops)

  Inputs have dimension D, there are C classes, and we operate on minibatches
  of N examples.

  Inputs:
  - W: A numpy array of shape (D, C) containing weights.
  - X: A numpy array of shape (N, D) containing a minibatch of data.
  - y: A numpy array of shape (N,) containing training labels; y[i] = c means
    that X[i] has label c, where 0 <= c < C.
  - reg: (float) regularization strength

  Returns a tuple of:
  - loss as single float
  - gradient with respect to weights W; an array of same shape as W
  """
  # Initialize the loss and gradient to zero.
  loss = 0.0
  dW = np.zeros_like(W)

  #############################################################################
  # TODO: Compute the softmax loss and its gradient using explicit loops.     #
  # Store the loss in loss and the gradient in dW. If you are not careful     #
  # here, it is easy to run into numeric instability. Don't forget the        #
  # regularization!                                                           #
  #############################################################################
  N, D = X.shape
  C = W.shape[1]
  for i in range(N):
    score = X[i].dot(W)
    score = score - np.max(score)  # numerical stable
    score = np.exp(score)
    loss += -np.log(score[y[i]] / np.sum(score))
    for j in range(C):
      out = score[j] / np.sum(score)
      if j == y[i]:
        dW[:, j] += (-1 + out) * X[i]
      else:
        dW[:, j] += out * X[i]
            
  loss /= N
  loss += 0.5 * reg * np.sum(W * W)
  dW /= N
  dW += reg * W
  #############################################################################
  #                          END OF YOUR CODE                                 #
  #############################################################################

  return loss, dW


def softmax_loss_vectorized(W, X, y, reg):
  """
  Softmax loss function, vectorized version.

  Inputs and outputs are the same as softmax_loss_naive.
  """
  # Initialize the loss and gradient to zero.
  loss = 0.0
  dW = np.zeros_like(W)

  #############################################################################
  # TODO: Compute the softmax loss and its gradient using no explicit loops.  #
  # Store the loss in loss and the gradient in dW. If you are not careful     #
  # here, it is easy to run into numeric instability. Don't forget the        #
  # regularization!                                                           #
  #############################################################################
  N, D = X.shape
  C = W.shape[1]
    
  scores = X.dot(W)
  scores -= np.max(scores, axis=1, keepdims=True)  # numerical stable
  scores = np.exp(scores)
  soft_scores = scores / np.sum(scores, axis=1, keepdims=True)
  loss = np.sum(-np.log(soft_scores[range(N), y])) / N
  loss += 0.5 * reg * np.sum(W * W)

  out = soft_scores.copy()
  out[range(N), y] += -1
  dW = X.T.dot(out) / N
  dW += reg * W
  #############################################################################
  #                          END OF YOUR CODE                                 #
  #############################################################################

  return loss, dW

