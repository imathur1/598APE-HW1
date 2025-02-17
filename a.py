import os
filedir = "output"
for file in os.listdir(filedir):
    if file.startswith("output"):
        # rename start of file with globe_correct
        os.rename(os.path.join(filedir, file), os.path.join(filedir, "globe_correct" + file[6:]))