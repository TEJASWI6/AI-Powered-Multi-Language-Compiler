# ai_engine/fixer.py
import google.generativeai as genai
import config

genai.configure(api_key=config.GOOGLE_API_KEY)

class AIFixer:
    def __init__(self, use_mock=False):
        self.use_mock = use_mock
        self.model = genai.GenerativeModel('gemini-flash-latest')

    def fix_code(self, broken_code, error_message, language, edu_mode=False):
        """Fixes broken code and optionally explains the fix."""
        if self.use_mock:
            return f"// Mock fixed {language} code"
            
        edu_instructions = ""
        if edu_mode:
            edu_instructions = """
            EDUCATIONAL MODE IS ON:
            - At the very top of the code, add a multi-line comment block.
            - Inside that comment block, explain exactly what the error was and WHY it crashed, in simple beginner terms.
            - Explain how your fix solves the problem.
            """
            
        try:
            prompt = f"""
            You are an expert {language} debugger and coding mentor.
            
            COMPILER ERROR MESSAGE:
            {error_message}
            
            BROKEN CODE:
            {broken_code}
            
            TASK:
            - Analyze the error and fix the code so it compiles and runs successfully.
            {edu_instructions}
            - Output ONLY the corrected raw {language} code (including the educational comments if requested). 
            - Keep the core logic intact.
            - NO markdown formatting (do not use ```).
            """
            
            response = self.model.generate_content(prompt)
            clean_code = response.text.replace(f"```{language.lower()}", "").replace("```", "").strip()
            return clean_code
            
        except Exception as e:
            return f"// AI Error: {e}\n{broken_code}"