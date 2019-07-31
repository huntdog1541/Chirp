entry()
{
    #case 0
    ###
    case 1
        case 1
    ###
###
case 2
        case 2
        ###

    ###case######3###

    int: a = 10 #9 9 case A # 9 still a comment until end of line
    a = 11

    int: b = 10 ### case B #### 9 this is a block comment followed by line comment
    b = 11

    ### case Bx
    9
    some text ###

    int: c = ### 9 case C 9 ### 10 
    c = 11

    int: d = 10 ### case D ###
    d = 11
 
    int: e = 10 ## 9 case E - still a single line comment
    e = 11
 
    int###case F###:###case F###f###case F###=###case F###10###case F###
    f = 11

    int### case G ###:### case G ### g ### case G ### = ### case G ### 10 ### case G ###
    g = 11
}
