# ai_engine/generator.py
import google.generativeai as genai
import config

genai.configure(api_key=config.GOOGLE_API_KEY)

class CodeGenerator:
    def __init__(self, use_mock=False):
        self.use_mock = use_mock
        # Using the standard fast model
        self.model = genai.GenerativeModel('gemini-flash-latest')

    def generate_code(self, english_prompt, language, edu_mode=False):
        """Generates code based on the user's selected language and mode."""
        if self.use_mock:
            return f"// Mock {language} code for testing"
        
        # If Educational Mode is ON, we add teaching instructions
        edu_instructions = ""
        if edu_mode:
            edu_instructions = """
            EDUCATIONAL MODE IS ON: 
            - Add detailed, beginner-friendly comments above every major line of logic.
            - Explain 'Like I'm 5' why you are using specific loops, variables, or math.
            """

        try:
            system_instruction = f"""
            You are an expert software engineer and coding mentor.
            
            USER REQUEST: "{english_prompt}"
            TARGET LANGUAGE: {language}
            
            TASK: 
            - Write a complete, runnable program in {language} that fulfills the request.
            - If {language} is Java, the public class MUST be named 'Main'.
            - If {language} is C, include standard libraries like <stdio.h> and a main() function.
            {edu_instructions}
            - Output ONLY the raw code. NO markdown formatting (do not use ```).
            """
            
            response = self.model.generate_content(system_instruction)
            clean_code = response.text.replace(f"```{language.lower()}", "").replace("```", "").strip()
            return clean_code
            
        except Exception as e:
            return f'// AI Error: {e}'