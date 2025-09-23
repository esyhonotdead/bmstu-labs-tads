#include "../inc/books.h"

void print_theader()
{
    printf("|           Фамилия            |           Название           |          Издательство        |        "
           "Кол-во страниц        |           Тип книги          |          Дополнительная информация          |\n");
    printf("|");
    for (size_t i = 0; i < 213; i++)
        printf("-");
    printf("|");
}

void print_tgenral(book_t book)
{
    printf("|");
    printf("%28s", book.author);
    printf("|");
    printf("%28s", book.name);
    printf("|");
    printf("%28s", book.publisher);
    printf("|");
    printf("%28zu", book.pages);
    printf("|");
    switch (book.etype)
    {
    case TECH:
        printf("%28s", BTECH_NAME);
        break;
    case FICT:
        printf("%28s", BTECH_NAME);
        break;
    case CHILD:
        printf("%28s", BTECH_NAME);
        break;
    }
}

void print_ttechb(book_t book)
{
    printf("|");
    printf("%30s", book.type.tech.industry);
    if (book.type.tech.native == true)
        printf("   Да");
    else
        printf("  Нет");
    printf("%10zu", book.type.tech.year_public);
    printf("|");
}

void print_tfictb(book_t book)
{
    printf("|");
    switch (book.type.fict.type)
    {
    case NOVEL:
        printf("%45s", TFICT_NOVEL);
        break;
    case PLAY:
        printf("%45s", TFICT_PLAY);
        break;
    case POESY:
        printf("%45s", TFICT_POESY);
        break;
    }
    printf("|");
}

void print_tchildb(book_t book)
{
    printf("|");
    printf("%15zu", book.type.child.min_age);
    switch (book.type.child.type)
    {
    case POETRY:
        printf("%45s", TCHILD_POETRY);
        break;
    case TALES:
        printf("%45s", TCHILD_TALES);
        break;
    }
    printf("|");
}

void print_table(books_t *books)
{
    print_theader();
    for (size_t i = 1; i < 3; i++)
    {
        if (books->data[i].etype == i)
        {
            print_tgenral(books->data[i]);
            print_ttechb(books->data[i]);
        }
    }
    printf("|");
    for (size_t i = 0; i < 213; i++)
        printf("-");
    printf("|");
}
