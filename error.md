1. echo
   - /bin/echo                      //OK
   - /bin/echo Hello                //OK
   - echo -n -n -n                  //OK
   - echo -nnnn                     //OK
   - echo hello                 a   //OK
   - echo                           //OK
   - echo Hello                     //OK
   - echo -n Hello                  //OK
   - echo -nnnn Hello               //OK
   - echo -n -n -n Hello            //OK
2. env와 export
   - 기본 동작
     - env, export                                      //OK
     - env a=b -> 한번만 등장 후 다음 env에서 사라져야함 -> X  //OK
   - 에러 처리 & exit status
     - env 1=2                                  //OK
     - env a    -> $?:127                       //OK
     - env =    -> $?: 1                        //OK
     - env a=b a=c b=d -> 한번 등장 후 사라져야함    //OK
     - export 1=a    -> $?: 1                   //OK
     - export a=====b                           //OK
     - export a                                 //OK
     - export a=b a=c b=d                       //OK
     - export a=                                //OK
3. unset
     - unset $HOME -> not a valid identifier    //OK
     - unset HOME 이후 cd                        //OK
     - export a=b 이후 unset a                   //OK
     - export a=b c=d 이후 unset a c             //OK
     - unset $PATH 이후 ls, cat 등               //OK
3. ls
   - /bin/ls -l .   //OK
   - /bin/ls        //OK
   - “ls -al”       //OK
   - “ls” “-al”     //OK
4. cd
   - 그냥 cd               //OK
   - cd $변수              //OK
   - cd -                 //OK
   - mkdir -p a/b/c/      //OK
     - rm -rf ../../a     //OK
     - pwd                //OK
     - cd ..              //OK
     - pwd                //OK
     - ...                //OK
   - cd | cd              //OK
5. exit
   - 기본 동작
     - exit 1  -> $?                                            //OK
   - exit 9999999999999999999999999999999999999999999999999     //OK
   - exit a                                                     //OK
   - exit                                                       //OK
   - exit 3                                                     //OK
   - exit 123                                                   //OK
6. 파이프라인 & 리다이렉션
   - exit 1 | exit 2          -> 2                              //OK
   - cat | cat | ls                                             //OK
   - sleep 10 | ls                                              //OK
   - ls -al > a>b>c                                             //OK
   - ls -al > a | cat        -> 표준 출력 x -> a로 들어가야 함        //OK
   - 에러처리
     - qwer > a | asdf >b                                       //OK
7. 문법 에러
   - ls >>      //OK
   - ls >>>     //OK
   - ls >>>>    //OK
8. 실행 파일
    - ./없는 파일         //OK
    - /없는 파일          //OK
    - 실행파일이 아닌 것    //OK
    - 쉘 스크립트 파일     //
9. Semicolons
    - echo Hello ; pwd ; ls                         //OK
    - echo Hello;pwd;ls                             //OK
    - echo Hello            ;  pwd        ;     ls  //OK
    - echo Hello ; exit ; echo World                //OK
10. Signal
    - Ctrl-C    //OK
    - Ctrl-D    //OK
    - Ctrl+\\   //OK
11. Double Quotes
    - echo “Hello” | cat -e                     //OK
    - echo “Hello                               //OK
    - echo ”  Hello ; echo 123       ” | cat -e //OK
    - echo ”  \\\\\\\\\\\\” “\\\\$HOME $HOME  ” //OK
    - echo “‘$HOME’”                            //OK
12. Environment Variables
    - echo $HOME    //OK
    - echo $PATH    //OK
    - echo “$HOME”  //OK
    - echo “$PATH”  //OK
    - echo ‘$HOME’  //OK
    - echo ‘$PATH’  //OK
13 ~ 14. cd + pwd
    - pwd, ls                            //OK
    - cd srcs -> pwd, ls                 //OK
    - cd . -> pwd, ls                    //OK
    - cd .. -> pwd, ls                   //OK
    - cd ../../../../../../../../../    //OK
    - cd ././././././././               //OK
    - cd ../../././../.././././../      //OK
    - cd invalid -> echo $?             //OK
15. Relative Path
    - ls -l                     //OK
    - cat srcs/main.c           //OK
    - ls -l ../../.././././../  //OK
16. Environment Path
    - ls -> unset PATH -> ls                    //OK
    - PATH에 가장 왼쪽에 있는 디렉터리 (path1 & path2) //??
17. Simple Quotes
    - echo ‘Hello’                          //OK
    - echo ‘Hello                           //OK
    - echo ‘’                               //OK
    - echo ‘$HOME’                          //OK
    - echo '  $HOME   ;  ; ; echo $PATH $ ' //OK
    - echo ‘\\\\\\\\\\\\\\\\“”"“’           //OK
    - echo ‘“$HOME”’                        //OK
18. Redirection
    - echo Hello > tmp (새로 만들어)        //OK
    - echo World >> tmp (추가모드)         //OK
    - cat < tmp                          //OK
    - grep int < srcs/main.c             //OK
    - echo Hello > tmp1 > tmp2 > tmp3    //OK
    - > tmp4 echo ABC                    //OK
    - ls -l > tmp6 | grep d              //OK
19. Pipe
    - cat /etc/passwd | grep ‘:’ | more //OK
    - ls -l | grep d                    //OK
    - ls invalid | grep d | more        //OK
    - ls -l | grep d > tmp5             //OK
20. Go Crazy
    - askdfjasdkhakdjfhadfhadjkadhfjkahdfjksdfuiyweuifhweuifhwuihfiwudhfiuwhdfuiwd
        //OK
    - echo a s k d f j a s d k h a k d j f h a d f h a d j k a d h f j k a h d f j k s d f u i y
        //OK
    - 0 : success (/bin/ls -l . -> echo $?)
        //OK
    - 1 : file not found (/bin/ls -l invalid -> echo $?)
        //OK
    - 127 : cmd not found (asdf)
        //OK
    - 126 : is dir (/bin)
        //OK
    - 258 : syntax error (>>>>>)
        //OK
    - 130 : child int (cat -> Ctrl-C)
        //OK
    - 131 : child quit (cat -> Ctrl-\\\\)
        //OK