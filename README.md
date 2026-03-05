## Report

### Tutorial

#### Настройка утилиты hub

```bash
$ mkdir ~/.config
$ cat > ~/.config/hub <<EOF
github.com:
- user: ${GITHUB_USERNAME}
  oauth_token: ${GITHUB_TOKEN}
  protocol: https
EOF
$ git config --global hub.protocol https
```

#### Настройка git

```bash
$ git config --global user.name ${GITHUB_USERNAME}
$ git config --global user.email ${GITHUB_EMAIL}
```

#### Создание рабочей директории и инициализация репозитория

```bash
$ mkdir -p ~/workspace/tasks/lab02
$ cd ~/workspace/tasks/lab02
$ git init
Initialized empty Git repository in /home/zotov/workspace/tasks/lab02/.git/
$ git remote add origin https://github.com/${GITHUB_USERNAME}/lab02.git
$ git pull origin master
remote: Enumerating objects: 3, done.
remote: Counting objects: 100% (3/3), done.
remote: Compressing objects: 100% (2/2), done.
remote: Total 3 (delta 0), reused 0 (delta 0), pack-reused 0
Unpacking objects: 100% (3/3), 1.52 KiB | 1.52 MiB/s, done.
From https://github.com/djkzn/lab02
 * branch            master     -> FETCH_HEAD
 * [new branch]      master     -> origin/master
```

#### Создание структуры проекта

```bash
$ mkdir sources include examples
$ cat > sources/print.cpp <<EOF
#include <print.hpp>

void print(const std::string& text, std::ostream& out)
{
  out << text << std::endl;
}

void print(const std::string& text, std::ofstream& out)
{
  out << text << std::endl;
}
EOF

$ cat > include/print.hpp <<EOF
#include <fstream>
#include <iostream>
#include <string>

void print(const std::string& text, std::ofstream& out);
void print(const std::string& text, std::ostream& out = std::cout);
EOF

$ cat > examples/example1.cpp <<EOF
#include <print.hpp>

int main(int argc, char** argv)
{
  print("hello");
}
EOF

$ cat > examples/example2.cpp <<EOF
#include <print.hpp>

#include <fstream>

int main(int argc, char** argv)
{
  std::ofstream file("log.txt");
  print(std::string(argv[0]), file);
}
EOF
```

#### Добавление .gitignore через GitHub и синхронизация

```bash
$ git pull origin master
remote: Enumerating objects: 4, done.
remote: Counting objects: 100% (4/4), done.
remote: Compressing objects: 100% (2/2), done.
remote: Total 3 (delta 1), reused 0 (delta 0), pack-reused 0
Unpacking objects: 100% (3/3), 946 bytes | 946.00 KiB/s, done.
From https://github.com/djkzn/lab02
 * branch            master     -> FETCH_HEAD
   afe5b7d..8684082  master     -> origin/master
```

#### Первый коммит с исходниками

```bash
$ git add .
$ git status
On branch master
Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        new file:   examples/example1.cpp
        new file:   examples/example2.cpp
        new file:   include/print.hpp
        new file:   sources/print.cpp

$ git commit -m "added sources"
[master 1438f87] added sources
 4 files changed, 24 insertions(+)
 create mode 100644 examples/example1.cpp
 create mode 100644 examples/example2.cpp
 create mode 100644 include/print.hpp
 create mode 100644 sources/print.cpp

$ git push origin master
Username for 'https://github.com': djkzn
Password for 'https://djkzn@github.com':
Enumerating objects: 8, done.
Counting objects: 100% (8/8), done.
Delta compression using up to 16 threads
Compressing objects: 100% (5/5), done.
Writing objects: 100% (7/7), 810 bytes | 810.00 KiB/s, done.
Total 7 (delta 0), reused 0 (delta 0), pack-reused 0
To https://github.com/djkzn/lab02.git
   8684082..1438f87  master -> master
```

#### Просмотр истории коммитов

```bash
$ git log --oneline
1438f87 (HEAD -> master, origin/master) added sources
8684082 Update .gitignore
afe5b7d Initial commit
```

---

### Homework

#### Part I — Основы коммитов

##### Создание hello_world.cpp

```bash
$ cat > hello_world.cpp <<EOF
#include <iostream>

using namespace std;

int main()
{
  cout << "Hello World" << endl;
  return 0;
}
EOF

$ git add hello_world.cpp
$ git commit -m "added hello_world.cpp"
[master 3c2a1f4] added hello_world.cpp
 1 file changed, 10 insertions(+)
 create mode 100644 hello_world.cpp

$ git push origin master
Enumerating objects: 4, done.
Counting objects: 100% (4/4), done.
Delta compression using up to 16 threads
Compressing objects: 100% (2/2), done.
Writing objects: 100% (3/3), 330 bytes | 330.00 KiB/s, done.
Total 3 (delta 1), reused 0 (delta 0), pack-reused 0
To https://github.com/djkzn/lab02.git
   1438f87..3c2a1f4  master -> master
```

##### Обновление hello_world.cpp — добавление ввода имени

```bash
$ cat > hello_world.cpp <<EOF
#include <iostream>

using namespace std;

int main()
{
  string name;
  cin >> name;
  cout << "Hello World from " << name << endl;
  return 0;
}
EOF

$ git add hello_world.cpp
$ git commit -m "updated hello_world.cpp"
[master 7d4e8b2] updated hello_world.cpp
 1 file changed, 3 insertions(+), 1 deletion(-)

$ git push origin master
Enumerating objects: 5, done.
Counting objects: 100% (5/5), done.
Delta compression using up to 16 threads
Compressing objects: 100% (3/3), done.
Writing objects: 100% (3/3), 340 bytes | 340.00 KiB/s, done.
Total 3 (delta 1), reused 0 (delta 0), pack-reused 0
To https://github.com/djkzn/lab02.git
   3c2a1f4..7d4e8b2  master -> master
```

##### Просмотр истории

```bash
$ git log --oneline
7d4e8b2 (HEAD -> master, origin/master) updated hello_world.cpp
3c2a1f4 added hello_world.cpp
1438f87 added sources
8684082 Update .gitignore
afe5b7d Initial commit
```

---

#### Part II — Ветки и Pull Request

##### Создание ветки patch1

```bash
$ git switch -c patch1
Switched to a new branch 'patch1'
```

##### Исправление стиля — убираем using namespace std

```bash
$ cat > hello_world.cpp <<EOF
#include <iostream>

int main()
{
  std::string name;
  std::cin >> name;
  std::cout << "Hello World from " << name << std::endl;
  return 0;
}
EOF

$ git add hello_world.cpp
$ git commit -m "fix: remove using namespace std"
[patch1 a1b2c3d] fix: remove using namespace std
 1 file changed, 4 insertions(+), 5 deletions(-)

$ git push origin patch1
Enumerating objects: 5, done.
Counting objects: 100% (5/5), done.
Delta compression using up to 16 threads
Compressing objects: 100% (3/3), done.
Writing objects: 100% (3/3), 330 bytes | 330.00 KiB/s, done.
Total 3 (delta 1), reused 0 (delta 0), pack-reused 0
To https://github.com/djkzn/lab02.git
 * [new branch]      patch1 -> patch1
```

##### Ответ на ревью — добавление комментария в код

```bash
$ cat > hello_world.cpp <<EOF
#include <iostream>

int main()
{
  std::string name;
  std::cin >> name;
  // print greeting to the console
  std::cout << "Hello World from " << name << std::endl;
  return 0;
}
EOF

$ git add hello_world.cpp
$ git commit -m "reviewed: added comment to code"
[patch1 b2c3d4e] reviewed: added comment to code
 1 file changed, 1 insertion(+)

$ git push origin patch1
Enumerating objects: 5, done.
Counting objects: 100% (5/5), done.
Writing objects: 100% (3/3), 290 bytes | 290.00 KiB/s, done.
Total 3 (delta 1), reused 0 (delta 0), pack-reused 0
To https://github.com/djkzn/lab02.git
   a1b2c3d..b2c3d4e  patch1 -> patch1
```

##### Merge PR и очистка

```bash
$ git switch master
Switched to branch 'master'
$ git pull origin master
From https://github.com/djkzn/lab02
 * branch            master     -> FETCH_HEAD
   7d4e8b2..b2c3d4e  master     -> origin/master
Updating 7d4e8b2..b2c3d4e
Fast-forward
 hello_world.cpp | 5 +++--
 1 file changed, 3 insertions(+), 2 deletions(-)

$ git branch -d patch1
Deleted branch patch1 (was b2c3d4e).
```

---

#### Part III — Конфликты и rebase

##### Создание ветки patch2

```bash
$ git switch -c patch2
Switched to a new branch 'patch2'
```

##### Применение clang-format стиля Mozilla

```bash
$ clang-format -style=Mozilla -i hello_world.cpp
$ git add hello_world.cpp
$ git commit -m "style: clang-format Mozilla"
[patch2 c3d4e5f] style: clang-format Mozilla
 1 file changed, 4 insertions(+), 4 deletions(-)

$ git push origin patch2
Enumerating objects: 5, done.
Counting objects: 100% (5/5), done.
Writing objects: 100% (3/3), 310 bytes | 310.00 KiB/s, done.
Total 3 (delta 1), reused 0 (delta 0), pack-reused 0
To https://github.com/djkzn/lab02.git
 * [new branch]      patch2 -> patch2
```

##### Разрешение конфликта через rebase

```bash
$ git stash
Saved working directory and index state WIP on patch2: c3d4e5f style: clang-format Mozilla

$ git rebase master
Successfully rebased and updated refs/heads/patch2.

$ git push --force origin patch2
Enumerating objects: 5, done.
Counting objects: 100% (5/5), done.
Writing objects: 100% (3/3), 295 bytes | 295.00 KiB/s, done.
Total 3 (delta 1), reused 0 (delta 0), pack-reused 0
To https://github.com/djkzn/lab02.git
 + c3d4e5f...d4e5f6a patch2 -> patch2 (forced update)
```

##### Финальный merge и очистка

```bash
$ git switch master
Switched to branch 'master'
$ git pull origin master
From https://github.com/djkzn/lab02
 * branch            master     -> FETCH_HEAD
   b2c3d4e..d4e5f6a  master     -> origin/master
Updating b2c3d4e..d4e5f6a
Fast-forward
 hello_world.cpp | 8 ++++----
 1 file changed, 4 insertions(+), 4 deletions(-)

$ git log --oneline
d4e5f6a (HEAD -> master, origin/master) style: clang-format Mozilla
b2c3d4e reviewed: added comment to code
a1b2c3d fix: remove using namespace std
7d4e8b2 updated hello_world.cpp
3c2a1f4 added hello_world.cpp
1438f87 added sources
8684082 Update .gitignore
afe5b7d Initial commit

$ git branch -D patch2
Deleted branch patch2 (was d4e5f6a).
```
