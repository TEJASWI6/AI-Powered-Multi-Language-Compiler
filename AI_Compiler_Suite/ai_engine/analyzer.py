# ai_engine/analyzer.py
import google.generativeai as genai
import config

genai.configure(api_key=config.GOOGLE_API_KEY)

class ComplexityAnalyzer:
    def __init__(self):
        self.model = genai.GenerativeModel('gemini-flash-latest')

    def analyze(self, code, language):
        prompt = f"""
        Act as an expert computer scientist. Analyze the following {language} code and calculate its Big-O time and space complexity.
        
        CODE:
        {code}
        
        TASK:
        1. State the Time Complexity (e.g., O(N^2), O(log N)).
        2. State the Space Complexity (e.g., O(1), O(N)).
        3. Provide a brief, 2-sentence explanation of WHY.
        4. If the time complexity is O(N^2) or worse, briefly suggest a Data Structure or algorithm approach to optimize it.
        
        Keep the response clean, professional, and easy to read.
        """
        try:
            response = self.model.generate_content(prompt)
            return response.text
        except Exception as e:
            return f"⚠️ Error analyzing complexity: {e}"