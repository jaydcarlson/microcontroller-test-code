;/*---------------------------------------------------------------------------------------------------------*/
;/*                                                                                                         */
;/* Copyright(c) 2013 Nuvoton Technology Corp. All rights reserved.                                         */
;/*                                                                                                         */
;/*---------------------------------------------------------------------------------------------------------*/


    AREA _image, DATA, READONLY

    EXPORT  loaderImage1Base
    EXPORT  loaderImage1Limit
    
    ALIGN   4
        
loaderImage1Base
    INCBIN ./obj/LDROM_code.bin
loaderImage1Limit

    END