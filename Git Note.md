# Git 笔记

## topics

- 创建版本库
- 时光机穿梭
- 远程仓库
- 分支管理
- 标签管理
- 自定义Git

## contents

### 1.创建版本库

- 生成目录

  ```
  $ mkdir learngit
  $ cd learngit
  $ pwd
  /Users/michael/learngit
  ```

  `pwd`命令用于显示当前目录

- 初始化一个Git仓库，使用`git init`命令。

  添加文件到Git仓库，分两步：

  1. 使用命令`git add <file>`，注意，可反复多次使用，添加多个文件；
  2. 使用命令`git commit -m <message>`，完成。

## 2.时光机穿梭

- 要随时掌握工作区的状态，使用`git status`命令。
- 如果`git status`告诉你有文件被修改过，用`git diff`可以查看修改内容。

### 版本回退

- `HEAD`指向的版本就是当前版本，因此，Git允许我们在版本的历史之间穿梭，使用命令`git reset --hard commit_id`。
  - 上一个版本就是`HEAD^`，上上一个版本就是`HEAD^^`，当然往上100个版本写100个`^`比较容易数不过来，所以写成`HEAD~100`。
- 穿梭前，用`git log`可以查看提交历史，以便确定要回退到哪个版本。
  - 如果嫌输出信息太多，可以试试加上`--pretty=oneline`参数
- 要重返未来，用`git reflog`查看命令历史，以便确定要回到未来的哪个版本。

### 工作区和暂存区

### 管理修改

- 现在，你又理解了Git是如何跟踪修改（而非跟踪文件）的，每次修改，如果不用`git add`到暂存区，那就不会加入到`commit`中。

### 撤销修改

- 场景1：当你改乱了工作区某个文件的内容，想直接丢弃工作区的修改时，用命令`git checkout -- file`。

- 场景2：当你不但改乱了工作区某个文件的内容，还添加到了暂存区时，想丢弃修改，分两步，第一步用命令`git reset HEAD <file>`，就回到了场景1，第二步按场景1操作。

- 场景3：已经提交了不合适的修改到版本库时，想要撤销本次提交，参考[版本回退](https://www.liaoxuefeng.com/wiki/0013739516305929606dd18361248578c67b8067c8c017b000/0013744142037508cf42e51debf49668810645e02887691000)一节，不过前提是没有推送到远程库。

### 删除文件

- 先在文件管理器中把没用的文件删了

- ```
  $ rm test.txt
  ```

- 现在你有两个选择，一是确实要从版本库中删除该文件，那就用命令`git rm`删掉，并且`git commit`

  ```
  $ git rm test.txt
  $ git commit -m "remove test.txt"
  ```

  另一种情况是删错了，因为版本库里还有呢，所以可以很轻松地把误删的文件恢复到最新版本：

  ```
  $ git checkout -- test.txt		
  ```

  - `git checkout`其实是用版本库里的版本替换工作区的版本，无论工作区是修改还是删除，都可以“一键还原”。

## 3.远程仓库

### 添加远程仓库

- 要关联一个远程库，使用命令`git remote add origin git@server-name:path/repo-name.git`

```
git remote add origin https://github.com/kyriiiiie/Algorithm.git
```

```
git remote add origin git@github.com:kyriiiiie/Algorithm.git 
```

- 关联后，使用命令`git push -u origin master`第一次推送master分支的所有内容；

- 此后，每次本地提交后，只要有必要，就可以使用命令`git push origin master`推送最新修改；

### 从远程仓库克隆

- ```
  git clone https://github.com/kyriiiiie/Algorithm.git
  ```

  ```
  Git clone git@github.com:kyriiiiie/Algorithm.git
  ```

- Git支持多种协议，默认的`git://`使用ssh，但也可以使用`https`等其他协议。

  使用`https`除了速度慢以外，还有个最大的麻烦是每次推送都必须输入口令，但是在某些只开放http端口的公司内部就无法使用`ssh`协议而只能用`https`。

## 3.分支管理

### 创建与合并分支

- 查看分支：`git branch`

- 创建分支：`git branch <name>`

- 切换分支：`git checkout <name>`

- 创建+切换分支：`git checkout -b <name>`

- 合并某分支到当前分支：`git merge <name>`

- 删除分支：`git branch -d <name>`

### 解决冲突

- 当Git无法自动合并分支时，就必须首先解决冲突。解决冲突后，再提交，合并完成。

- 解决冲突就是把Git合并失败的文件手动编辑为我们希望的内容，再提交。

- 用`git log --graph`命令可以看到分支合并图。

### 分支管理策略

- 合并分支时，加上`--no-ff`参数就可以用普通模式合并，合并后的历史有分支，能看出来曾经做过合并，而`fast forward`合并就看不出来曾经做过合并

  - ```
     merge: 
     git merge --no-ff -m "merge with no-ff" dev
     
     look back
     git log --graph --pretty=oneline --abbrev-commit
    ```

- 在实际开发中，我们应该按照几个基本原则进行分支管理：

  首先，`master`分支应该是非常稳定的，也就是仅用来发布新版本，平时不能在上面干活；

  那在哪干活呢？干活都在`dev`分支上，也就是说，`dev`分支是不稳定的，到某个时候，比如1.0版本发布时，再把`dev`分支合并到`master`上，在`master`分支发布1.0版本；

  你和你的小伙伴们每个人都在`dev`分支上干活，每个人都有自己的分支，时不时地往`dev`分支上合并就可以了。

### Bug分支

- 修复bug时，我们会通过创建新的bug分支进行修复，然后合并，最后删除；

- 当手头工作没有完成时，先把工作现场`git stash`一下，然后去修复bug，修复后，再`git stash pop`，回到工作现场。

  ```
  查看暂存的工作现场：
  git stash list
  恢复工作现场同时把stash内容删除：
  git stash pop
  恢复制定的stash：
  git stash apply stash@{?}
  ```

### Feature分支

- 软件开发中，总有无穷无尽的新的功能要不断添加进来。添加一个新功能时，你肯定不希望因为一些实验性质的代码，把主分支搞乱了，所以，每添加一个新功能，最好新建一个feature分支，在上面开发，完成后，合并，最后，删除该feature分支。

- 如果要丢弃一个没有被合并过的分支，可以通过`git branch -D <name>`强行删除。

### 多人协作

- 查看远程库信息，使用`git remote -v`；
- 本地新建的分支如果不推送到远程，对其他人就是不可见的；
- 从本地推送分支，使用`git push origin branch-name`，如果推送失败，先用`git pull`抓取远程的新提交；
- 在本地创建和远程分支对应的分支，使用`git checkout -b branch-name origin/branch-name`，本地和远程分支的名称最好一致；
- 建立本地分支和远程分支的关联，使用`git branch --set-upstream branch-name origin/branch-name`；
- 从远程抓取分支，使用`git pull`，如果有冲突，要先处理冲突。

- 因此，多人协作的工作模式通常是这样：

  1. 首先，可以试图用`git push origin <branch-name>`推送自己的修改；
  2. 如果推送失败，则因为远程分支比你的本地更新，需要先用`git pull`试图合并；
  3. 如果合并有冲突，则解决冲突，并在本地提交；
  4. 没有冲突或者解决掉冲突后，再用`git push origin <branch-name>`推送就能成功！

  如果`git pull`提示`no tracking information`，则说明本地分支和远程分支的链接关系没有创建，用命令`git branch --set-upstream-to <branch-name> origin/<branch-name>`。

### Rebase

-  把历史信息显示变直。。

## 4.标签管理

### 使用github

- 在GitHub上，可以任意Fork开源仓库；
- 自己拥有Fork后的仓库的读写权限；
- 可以推送pull request给官方仓库来贡献代码。