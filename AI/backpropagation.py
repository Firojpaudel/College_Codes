import numpy as np 

## Defining the activation function 
def sigmoid(x):
    return 1/(1+np.exp(-x))

## Then lets also define the derivative if the sigmoid function 
def sig_der(x):
    return x*(1-x)

## Training function: for XOR
def train_NN(X, y, epochs, alpha):
    #@ Fist: Seeding
    np.random.seed(42)
    #@ Weights 
    ''' 
        Here, I will be using the Neural Net of 2 input nodes, 2 hidden layers with 3 nodes each and 
        one output node.
    '''
    weights_input_hidden1 = np.random.uniform(size=(2,3)) # ie, from input to hidden layer 1
    weights_hidden1_hidden2 = np.random.uniform(size=(3,3)) # ie, from hidden layer 1 to hidden layer 2
    weights_hidden2_output = np.random.uniform(size=(3,1)) # ie, from hidden layer 2 to output layer
    #@ Biases
    bias_hidden1 = np.random.uniform(size=(1,3))
    bias_hidden2 = np.random.uniform(size=(1,3))
    bias_output = np.random.uniform(size=(1,1))
    
    for epoch in range(epochs):
        #@ First: Forward Propagation
        hidden1_input = np.dot(X, weights_input_hidden1) + bias_hidden1
        '''
            Just a normal forward prop formula: Wx + b
        '''
        hidden1_activation = sigmoid(hidden1_input)
        '''
            Applying the activation function to the hidden layer 1
        '''
        
        hidden2_input = np.dot(hidden1_activation, weights_hidden1_hidden2) + bias_hidden2
        hidden2_activation = sigmoid(hidden2_input)
        
        output_input = np.dot(hidden2_activation, weights_hidden2_output) + bias_output
        predicted_output = sigmoid(output_input)
        
        #@ Error Calculation 
        E = y - predicted_output
        
        #@ BackProp
        
        d_error = E * sig_der(predicted_output)  # ie, derivative of the error
        
        error_hidden2 = d_error.dot(weights_hidden2_output.T) # ie, error in hidden layer 2
        '''
            The formula: error = error * weights.T where T is the transpose of the weights
        '''
        
        d_hidden2 = error_hidden2 * sig_der(hidden2_activation) # ie, derivative of the hidden layer 2
        
        error_hidden1 = d_hidden2.dot(weights_hidden1_hidden2.T)
        d_hidden1 = error_hidden1 * sig_der(hidden1_activation)
        
        #@ Weights and Bias Update using the partial derivative
        weights_hidden2_output += hidden2_activation.T.dot(d_error) * alpha 
        '''
            The formula: weights = weights + input.T * error * learning_rate
        '''
        bias_output += np.sum(d_error,axis=0,keepdims=True) * alpha 
        '''
            The formula: bias = bias + sum(error) * learning_rate
        '''
        
        weights_hidden1_hidden2 += hidden1_activation.T.dot(d_hidden2) * alpha
        bias_hidden2 += np.sum(d_hidden2,axis=0,keepdims=True) * alpha
        
        weights_input_hidden1 += X.T.dot(d_hidden1) * alpha
        bias_hidden1 += np.sum(d_hidden1,axis=0,keepdims=True) * alpha
        
        ##@ Log details for every 1000 epochs
        if epoch % 1000 == 0:
            print(f"Epoch {epoch}: Error: {np.mean(np.abs(E))}")
    
    return weights_input_hidden1, weights_hidden1_hidden2, weights_hidden2_output, \
        bias_hidden1, bias_hidden2, bias_output, predicted_output

#@ So here is the input for the XOR gate:
X= np.array([
    [0,0],
    [0,1],
    [1,0],
    [1,1]
]) 

y= np.array([
    [0],
    [1],
    [1],
    [0]
]) 

#@ Trainig parameters:
epoch = 10000
alpha = 0.5  # ie, learning rate

#@ Train the neural net
weights_input_hidden1, weights_hidden1_hidden2, weights_hidden2_output, \
    bias_hidden1, bias_hidden2, bias_output, predicted_output = train_NN(X, y, epoch, alpha)
    
#@ Displaying the results
print("\nTraining Complete!\n")
print("Final Predictions:")
print("\nInput -> Predicted (Target)")
for i in range(len(X)):
    print(f"{X[i]} -> {predicted_output[i][0]:.4f} ({y[i][0]})")

#@ Also, lets show the partial derivative updates 
print("\nFinal Weights and Biases:")
print("\nWeights (Input to Hidden Layer 1):")
print(weights_input_hidden1)
print("\nWeights (Hidden Layer 1 to Hidden Layer 2):")
print(weights_hidden1_hidden2)
print("\nWeights (Hidden Layer 2 to Output):")
print(weights_hidden2_output)
print("\nBiases (Hidden Layer 1):")
print(bias_hidden1)
print("\nBiases (Hidden Layer 2):")
print(bias_hidden2)
print("\nBiases (Output Layer):")
print(bias_output)


  
        
    
    
    