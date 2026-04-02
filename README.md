# Отчёт по лабораторной работе №2
## Работа с Git: ветки, Pull Request, rebase

**Студент:** Зотов  
**Дата:** 02.04.2026  
**Репозиторий:** https://github.com/djkzn/HW2

---

## Цель работы

Освоить базовые операции системы контроля версий Git: создание коммитов, работу с ветками, отправку изменений на GitHub, создание Pull Request и разрешение конфликтов при rebase.

---

## Ход выполнения работы

### 1. Клонирование репозитория

Был склонирован заранее созданный репозиторий `HW2` с GitHub:

```bash
zotov@zephyrus:~/workspace/tasks$ git clone https://github.com/djkzn/HW2.git
zotov@zephyrus:~/workspace/tasks$ cd HW2
```

<details>
<summary>Вывод git clone</summary>

```
Cloning into 'HW2'...
remote: Enumerating objects: 3, done.
remote: Counting objects: 100% (3/3), done.
remote: Total 3 (delta 0), reused 0 (delta 0), pack-reused 0 (from 0)
Receiving objects: 100% (3/3), done.
```

</details>

---

### 2. Создание файла и первые коммиты

В редакторе Sublime Text был создан файл `hello_world.cpp`. После этого он был добавлен в индекс и закоммичен:

```bash
zotov@zephyrus:~/workspace/tasks/HW2$ subl hello_world.cpp
zotov@zephyrus:~/workspace/tasks/HW2$ git add hello_world.cpp
zotov@zephyrus:~/workspace/tasks/HW2$ git commit -m "added hello_world.cpp"
[main 67d4d54] added hello_world.cpp
 1 file changed, 7 insertions(+)
 create mode 100644 hello_world.cpp
```

Затем файл был доработан (добавлено имя пользователя). При попытке закоммитить без `git add` Git сообщил, что изменения не проиндексированы:

```bash
zotov@zephyrus:~/workspace/tasks/HW2$ git commit -m "added hello_world.cpp with user name"
On branch main
Changes not staged for commit:
        modified:   hello_world.cpp
no changes added to commit (use "git add" and/or "git commit -a")
```

Ошибка была исправлена флагом `-a`, который автоматически индексирует изменённые файлы:

```bash
zotov@zephyrus:~/workspace/tasks/HW2$ git commit -am "added hello_world.cpp with user name"
[main 5aae6f5] added hello_world.cpp with user name
 1 file changed, 4 insertions(+), 2 deletions(-))
```

---

### 3. Публикация на GitHub

При попытке отправить ветку под именем `master` возникла ошибка — ветка называется `main`:

```bash
zotov@zephyrus:~/workspace/tasks/HW2$ git push -u origin master
error: src refspec master does not match any
error: failed to push some refs to 'https://github.com/djkzn/HW2.git'
```

После указания верного имени ветки `main` push прошёл успешно:

```bash
zotov@zephyrus:~/workspace/tasks/HW2$ git push origin main
```

<details>
<summary>Вывод git push origin main</summary>

```
Enumerating objects: 7, done.
Counting objects: 100% (7/7), done.
Delta compression using up to 24 threads
Compressing objects: 100% (6/6), done.
Writing objects: 100% (6/6), 847 bytes | 282.00 KiB/s, done.
Total 6 (delta 0), reused 0 (delta 0), pack-reused 0
To https://github.com/djkzn/HW2.git
   2c8df17..5aae6f5  main -> main
```

</details>

---

### 4. Ветка `patch1` — рефакторинг и Pull Request

Была создана ветка `patch1` для рефакторинга кода:

```bash
zotov@zephyrus:~/workspace/tasks/HW2$ git checkout -b patch1
Switched to a new branch 'patch1'
```

В файл были внесены правки (удаление `using namespace std;`), затем выполнен коммит и отправка ветки на GitHub:

```bash
zotov@zephyrus:~/workspace/tasks/HW2$ git add hello_world.cpp
zotov@zephyrus:~/workspace/tasks/HW2$ git commit -m "fix: remove using namespace std;"
[patch1 6f81a5c] fix: remove using namespace std;
 1 file changed, 4 insertions(+), 4 deletions(-)
zotov@zephyrus:~/workspace/tasks/HW2$ git push origin patch1
```

<details>
<summary>Вывод git push origin patch1</summary>

```
Enumerating objects: 5, done.
Counting objects: 100% (5/5), done.
Delta compression using up to 24 threads
Compressing objects: 100% (3/3), done.
Writing objects: 100% (3/3), 412 bytes | 206.00 KiB/s, done.
Total 3 (delta 0), reused 0 (delta 0), pack-reused 0
remote:
remote: Create a pull request for 'patch1' on GitHub by visiting:
remote:      https://github.com/djkzn/HW2/pull/new/patch1
remote:
To https://github.com/djkzn/HW2.git
 * [new branch]      patch1 -> patch1
```

</details>

Аналогично предыдущему разу, попытка коммита без индексации была исправлена флагом `-a`. Добавлен второй коммит с комментариями в коде:

```bash
zotov@zephyrus:~/workspace/tasks/HW2$ git commit -am "add comments"
[patch1 5f89b40] add comments
 1 file changed, 2 insertions(+), 2 deletions(-)
zotov@zephyrus:~/workspace/tasks/HW2$ git push origin patch1
```

На GitHub был создан и смёрджен Pull Request `#1`. После этого ветка `main` была обновлена локально:

```bash
zotov@zephyrus:~/workspace/tasks/HW2$ git checkout main
zotov@zephyrus:~/workspace/tasks/HW2$ git pull origin main
```

<details>
<summary>Вывод git pull + git log</summary>

```
Unpacking objects: 100% (1/1), 899 bytes | 224.00 KiB/s, done.
From https://github.com/djkzn/HW2
 * branch            main       -> FETCH_HEAD
   5aae6f5..c38b880  main       -> origin/main
Updating 5aae6f5..c38b880
Fast-forward
 hello_world.cpp | 8 ++++----
 1 file changed, 4 insertions(+), 4 deletions(-)

commit c38b88024254ad893b8afdea9a8924896139f173 (HEAD -> main, origin/main)
Merge: 5aae6f5 5f89b40
Author: djkzn <zotov2007@gmail.com>
Date:   Thu Apr 2 10:52:17 2026 +0300

    Merge pull request #1 from djkzn/patch1

    fix: remove using namespace std;

commit 5f89b406dbed9e6ac74fa48c6d35aacc9ebc6bdd (origin/patch1, patch1)
    add comments

commit 6f81a5c9cb885120457cc88298fd9103dea672ae
    fix: remove using namespace std;

commit 5aae6f5a275cc88743c671d6a6359211a557ea3b
    added hello_world.cpp with user name

commit 67d4d540da3f000abdceabfd22235ce45ad86041
    added hello_world.cpp

commit 2c8df170f036a085330a5e1b28efd5df94ceeef4
    Initial commit
```

</details>

Ветка `patch1` была удалена локально:

```bash
zotov@zephyrus:~/workspace/tasks/HW2$ git branch -d patch1
Deleted branch patch1 (was 5f89b40).
```

---

### 5. Ветка `patch2` — форматирование и rebase с конфликтом

Была создана ветка `patch2` для применения автоматического форматирования кода через `clang-format`:

```bash
zotov@zephyrus:~/workspace/tasks/HW2$ git checkout -b patch2
zotov@zephyrus:~/workspace/tasks/HW2$ clang-format -style=Mozilla -i hello_world.cpp
zotov@zephyrus:~/workspace/tasks/HW2$ git commit -am "apply clang-format Mozilla style"
[patch2 67eab49] apply clang-format Mozilla style
 1 file changed, 7 insertions(+), 5 deletions(-)
zotov@zephyrus:~/workspace/tasks/HW2$ git push origin patch2
```

После создания и merge Pull Request `#2` на GitHub ветка `main` ушла вперёд. При попытке rebase возник конфликт:

```bash
zotov@zephyrus:~/workspace/tasks/HW2$ git checkout patch2
zotov@zephyrus:~/workspace/tasks/HW2$ git rebase main
```

<details>
<summary>Вывод git rebase (конфликт)</summary>

```
Auto-merging hello_world.cpp
CONFLICT (content): Merge conflict in hello_world.cpp
error: could not apply 67eab49... apply clang-format Mozilla style
hint: Resolve all conflicts manually, mark them as resolved with
hint: "git add/rm <conflicted_files>", then run "git rebase --continue".
hint: You can instead skip this commit: run "git rebase --skip".
hint: To abort and get back to the state before "git rebase", run "git rebase --abort".
Could not apply 67eab49... apply clang-format Mozilla style
```

</details>

Конфликт был разрешён вручную, после чего rebase продолжен:

```bash
zotov@zephyrus:~/workspace/tasks/HW2$ git add hello_world.cpp
zotov@zephyrus:~/workspace/tasks/HW2$ git rebase --continue
[detached HEAD 0988079] apply clang-format Mozilla style
 1 file changed, 7 insertions(+), 5 deletions(-)
Successfully rebased and updated refs/heads/patch2.
```

Так как история ветки изменилась после rebase, потребовался force push:

```bash
zotov@zephyrus:~/workspace/tasks/HW2$ git push origin patch2 --force
```

<details>
<summary>Вывод git push --force</summary>

```
Enumerating objects: 5, done.
Counting objects: 100% (5/5), done.
Delta compression using up to 24 threads
Compressing objects: 100% (3/3), done.
Writing objects: 100% (3/3), 380 bytes | 190.00 KiB/s, done.
Total 3 (delta 1), reused 0 (delta 0), pack-reused 0
remote: Resolving deltas: 100% (1/1), completed with 1 local object.
To https://github.com/djkzn/HW2.git
 + 67eab49...0988079 patch2 -> patch2 (forced update)
```

</details>

---

## Вывод

В ходе лабораторной работы были освоены ключевые операции Git: создание и индексирование коммитов, публикация веток на GitHub (`git push`), создание Pull Request, слияние изменений через `git pull`. Были разобраны типичные ошибки: попытка закоммитить без `git add` и push в несуществующую ветку `master`. Отдельно отработан сценарий `git rebase` с возникновением конфликта, его ручным разрешением через `git add` + `git rebase --continue` и последующим `git push --force`.
