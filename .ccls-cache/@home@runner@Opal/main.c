int main()
{
    int array[10] = {0,1,0,1,1,0,1,1,1,0,0};
    char array2[10];
    int i;
    for(i=0;i<10;i++)
    {
        array2[i] = array[i];
        printf("%c %d\n", '0' + array2[i],array2[i]);
    }

}