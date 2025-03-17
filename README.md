# enwiki


This extension has some specific features for the English Wikipedia.

Note: This extension should be checked out in the folder named "huggle" in your `huggle3-qt-lx` repo.

## How to build

### On Windows:
You need to build the Huggle core library first. Once you complete that, open the `.pro` file and ensure the include path is pointing to the folder with Huggle's source code. All of Huggle's header files can be included. Copy the Huggle core library to the `src` folder of the extension.

Now, try to build it. The `.dll` file it produces needs to be copied to `extensions` folder.

### On Linux:
Make sure that the `include` folder points to the huggle folder. Next, build the library and copy the `.so` file to the proper extensions path.
