<img src="/LOGO.png" width="400" />

# WinTask
A very lightweight CLI Command Task Manager for Windows.

## System Requirements.
  #### OS :: Windows 7 Service Pack 1 x64 or later
  #### Storage :: 10 MB


## How to use
To start using WinTask. First install it <br>
Then find where its installed (usually C:\WinTask), And then remeber it. <br>
Now you can check the version by doing: `<install-dir>\wintask.exe /?` <br>
  Example: `C:\WinTask\wintask.exe /?`

To run tasks first go to a directory of your choice. Create a `wintask.json` file.<br>
Then add entries for tasks, And in the entries should be nested json. they should contain a `commands` that'll contain all the commands for that task.<br>
Example:<br>
```json
{
  "print_hello": {
    "commands": ["echo hello"]
  },
  "print_hi": {
    "commands": ["echo hi"]
  }
}
```
Lastly, to run a task, obvisouly make sure you're in the folder where you created the .json file.<br>
Run `<install-dir>\wintask.exe /run <task-name>`<br>
Example: `C:\WinTask\wintask.exe /run print_hello` and `C:\WinTask\wintask.exe /run print_hi`



## Support for Linux and macOS
Unfortunately, there isn't support for these OSs rn.<br>
But you can compile the source (Its simple)<br>
- Here's how:
1. Install git and ninja
> Linux: "dnf/yum/apt install git ninja" or "pacman -S git ninja"
> macOS: "brew install git ninja"
2. Clone repository
> Clone the repository using `git clone https://github.com/devpython88/WinTask`
3. Change directory
> CD into build using `cd /path/to/folder/where/wintask/is/cloned/` and then `cd build`
4. Build
> Build by running `ninja`, it'll take a few minutes
5. Done.
