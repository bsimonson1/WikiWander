import pandas as pd

# Read the text file, skipping the first row and assuming space as the delimiter
read_file = pd.read_csv(
    r'C:\Users\bengs\OneDrive\Desktop\WikiRace\enwiki-2013.txt', 
    delimiter=' ', 
    skiprows=4, 
    names=['FromNodeId', 'ToNodeId']
)

# Write to a CSV file
read_file.to_csv(
    r'C:\Users\bengs\OneDrive\Desktop\WikiRace\wikirace.csv', 
    index=None
)