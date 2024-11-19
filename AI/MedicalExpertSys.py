'''
    This code is for the Expert System of the Medical Diagnosis System. Not part of practicals.
'''

class ExpertSystem:
    def __init__(self):
        self.knowledgeBase = {
            'Symptoms': ['Fever', 'Cough', 'Sore Throat', 'Body Ache', 'Headache', 'Chills', 'Fatigue', 'Runny Nose'],
            'Diseases': ['Flu', 'Common Cold', 'Allergies', 'COVID-19'],
            'Flu': ['Fever', 'Cough', 'Sore Throat', 'Body Ache', 'Headache', 'Chills', 'Fatigue'],
            'Common Cold': ['Fever', 'Cough', 'Sore Throat', 'Runny Nose'],
            'Allergies': ['Cough', 'Sore Throat', 'Runny Nose'],
            'COVID-19': ['Fever', 'Cough', 'Sore Throat', 'Body Ache', 'Headache', 'Chills', 'Fatigue', 'Runny Nose']
        }
        self.diagnose = []

    def welcome(self):
        print("Welcome to the Medical Diagnosis Expert System!")
        print("Answer the following questions with Yes or No (y/n) \n")

    def askSymptoms(self):
        for symptom in self.knowledgeBase['Symptoms']:
            answer = input(f"Do you have {symptom}? ").strip().lower()
            if answer in ['yes', 'y']:
                self.diagnose.append(symptom)

    def diagnoseDisease(self):
        print("\nDiagnosing based on the symptoms...\n")
        disease_score = {}

        # Calculate symptom matches for each disease
        for disease in self.knowledgeBase['Diseases']:
            disease_score[disease] = 0
            for symptom in self.knowledgeBase[disease]:
                if symptom in self.diagnose:
                    disease_score[disease] += 1

        # Find diseases with maximum symptom matches
        max_score = max(disease_score.values())
        probable_diseases = [disease for disease, score in disease_score.items() if score == max_score and score > 0]

        # Display results
        if probable_diseases:
            print("Based on your symptoms, you might have:")
            for disease in probable_diseases:
                print(f"- {disease} ({disease_score[disease]} symptom(s) matched)")
        else:
            print("Sorry, we couldn't determine a specific condition based on your symptoms.")
        print("\nPlease consult a medical professional for an accurate diagnosis.")

    def run(self):
        self.welcome()
        self.askSymptoms()
        self.diagnoseDisease()


if __name__ == "__main__":
    system = ExpertSystem()
    system.run()
