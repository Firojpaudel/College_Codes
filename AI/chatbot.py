# Creating a chatbot using python 
def get_response(user_input):
    # Defining some basic responses using a dictionary ...
    responses = {
        "hi": "Hello! How can I help you today?",
        "hey": "Hello! How can I help you today?",
        "hello": "Hello! How can I help you today?",
        "how are you": "I'm just a bot, but I'm doing well. How about you?",
        "bye": "Goodbye! Have a great day!",
        "what's your name": "I'm a chatbot created by you. Call me Brandy!",
        "hey Brandy": "Hello! How can I help you today?",
        "brandy": "Yes, that's me! How can I help you today?",
        "what can you do": "I can help you with a variety of things. Try asking me about the weather, or for a joke!",
        "how's the weather": "I'm not sure. You should check your weather app!",
        "tell me a joke": "Why did the computer go to the doctor? Because it had a virus!",
    }
    
    # Normalizing user input so that it's case-insensitive
    user_input = user_input.lower().strip()
    
    # Getting response based on user input
    return responses.get(user_input, "Sorry, I didn't understand that.")

def chat():
    print("Welcome to the chatbot! Type 'bye' to end the chat.\n")
    while True:
        user_input = input("You: ")
        response = get_response(user_input)
        print("Chatbot:", response)
        if user_input.lower() == "bye":
            break


if __name__ == "__main__":
    chat()