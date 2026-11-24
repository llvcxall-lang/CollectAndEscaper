# دليل رفع المشروع على GitHub خطوة بخطوة (3 Commits للمراحل)

لكي يظهر في مستودعك على GitHub تسلسل التطوير المرحلي المطلوب (Stage 1 -> Stage 2 -> Stage 3):

1. أنشئ مستودعاً جديداً على GitHub باسم `CollectAndEscape` (بدون بيانات شخصية).
2. انسخ الملفات إلى مجلد المشروع على جهازك وافتح الطرفية (Terminal) داخله:
```bash
git init
git branch -M main
git remote add origin https://github.com/YOUR_USERNAME/CollectAndEscape.git
```
3. **المرحلة 1 (Stage 1):**
```bash
git add GameConfig.h Player.h Player.cpp Coin.h Coin.cpp
git commit -m "Stage 1: Working player movement, boundaries, and 5 coins scoring"
git push -u origin main
```
4. **المرحلة 2 (Stage 2):**
```bash
git add Enemy.h Enemy.cpp PatrolEnemy.h PatrolEnemy.cpp ChaseEnemy.h ChaseEnemy.cpp
git commit -m "Stage 2: Enemy OOP hierarchy, polymorphism, and cooldown logic"
git push
```
5. **المرحلة 3 (Stage 3 - اللعبة الكاملة والتوثيق):**
```bash
git add Game.h Game.cpp main.cpp Makefile README.md Project_Documentation_3Pages.md
git commit -m "Stage 3: Complete game states, win/lose priority, and documentation"
git push
```
6. **عند التسليم النهائي:**
   - غيّر اسم المجلد إلى رقمك الجامعي: `StudentID_CollectAndEscape` (مثلاً `U26101234_CollectAndEscape`).
   - تأكد من عدم وجود مجلد `.git` أو ملفات `.o` / `.exe` المؤقتة داخل ملف الـ ZIP النهائي، واختبر ترجمته من مجلد جديد نظيف قبل الرفع.
