# Step 1: Create a variable to hold the text we want to reverse.
# Think of a variable like a labeled box. We are putting the word "Hello" into a box named 'original_string'.
original_string = "Hello World"

# Step 2: Reverse the string using Python's special "slicing" technique.
# ELI5: Imagine a row of toy blocks. The [::-1] part is like a magic instruction that says:
# "Start at the very last block, move backwards one step at a time, and keep going until you hit the start."
# In Python, the format is [start:stop:step]. By leaving start and stop empty and using -1 for the step,
# we tell the computer to walk through the entire string in reverse.
reversed_string = original_string[::-1]

# Step 3: Use the 'print' command to show our result on the screen.
# This is like holding up a sign so everyone can see what is inside our 'reversed_string' box.
print("Original:", original_string)
print("Reversed:", reversed_string)

# Alternative method: Using a loop to understand how it works manually.
# We create an empty string box to store our letters one by one.
manual_reversed = ""

# Step 4: Use a 'for' loop to look at every letter in the original text.
# ELI5: This is like a teacher pointing to every child in a line, one by one.
for character in original_string:
    # We take the current letter and put it at the FRONT of our new string.
    # ELI5: If we have "A" and then get "B", we put "B" before "A" to get "BA".
    # Doing this over and over flips the whole word!
    manual_reversed = character + manual_reversed

# Step 5: Print the result from our manual loop method.
print("Manual Loop Result:", manual_reversed)