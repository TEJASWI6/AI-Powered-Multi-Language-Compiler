# check_models.py
import google.generativeai as genai
import config

genai.configure(api_key=config.GOOGLE_API_KEY)

print("🔍 Searching for available models...")
try:
    for m in genai.list_models():
        if 'generateContent' in m.supported_generation_methods:
            print(f"✅ FOUND: {m.name}")
except Exception as e:
    print(f"❌ Error: {e}")