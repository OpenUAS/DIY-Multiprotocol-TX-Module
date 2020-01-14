/*
 * This file is meant to keep **OUR* settings after an upgrade of the multi source.
 * Tailored for OpenUAS  MX22 and Taranis and others to have all possible options needed
 * Using Telemetry, PPM and serial
 * The MX22's has a extra telemetry display added
 * For the MX22 if Devo or Walkera protocol is used we need to swap Collective and Throttle on a heli mode
 * but only needed if we fly the original Walkera electronics, for and
 * autopilot equiped aircraft we can do whatever we want with servo output, we are fully flexible in that case anyhow
 */


/* Below, well, yes ehhh... comment the line when done debugging... */
//#define DEBUG_SERIAL //Well, yes ehhh...comment when done debugging...

/* Just a regular 4in1 module but with all **OUR** specific settings, after all we own the _MyConfig.h and can set whatever we need. */
#define TXMODULE_OPENUAS_DEFAULT

/* We rather would have one exact same config but frequency tuning is different per module for some CC2500 protocols as well as some settings. Sad, but it is what it is... */

//#define TXMODULE_NR_1 /* MX22 Main */
//#define TXMODULE_NR_2 /* MX 22 Backup */
//#define TXMODULE_NR_3 /* X9D type*/
//#define TXMODULE_NR_4 /* Extended MC24 */
#define TXMODULE_NR_5   /* Xlite */
//#define TXMODULE_NR_6 /* Devo10 */

/* ----------------------------------------------------- */
/* ----------------------------------------------------- */
/* ----------------------------------------------------- */
/* No need to to change anything below this line anymore */

#ifdef TXMODULE_NR_1
  #define TX_OPENUAS_MX22
  #define FRQ_TUNE 20
#endif

#ifdef TXMODULE_NR_2
  #define TX_OPENUAS_MX22
  #define FRQ_TUNE 20
#endif

#ifdef TXMODULE_NR_3
  #define FRQ_TUNE 20
#endif

#ifdef TXMODULE_NR_4
  #define TX_OPENUAS_MX22
  #define FRQ_TUNE 20
#endif

#ifdef TXMODULE_NR_5
  #define FRQ_TUNE 20
#endif

#ifdef TXMODULE_NR_6
  #define TX_OPENUAS_MX22
  #define FRQ_TUNE 20
#endif

#ifdef TXMODULE_OPENUAS_DEFAULT

  /* The blink time is to low to see well in full sunlight as ofter the case in the field so we make it longer. Well, since we now only have one bank, it does not matter ATM. */
  #undef BLINK_BANK_TIME_HIGH
  #define BLINK_BANK_TIME_HIGH    100

  #ifdef TX_OPENUAS_MX22
    #ifdef TX_ER9X
      #undef TX_ER9X
    #endif
    #ifdef TX_SPEKTRUM
      #undef TX_SPEKTRUM
    #endif

    /* The CH6 and CH1 should be swapped since collective and curves are fixed of CH1 PPM out of Graupner/JR PPM Transmitters, so we link into the PPM steam and swap the output */
    #define COLLECTIVE 0  //This OWN define is used to make a difference so we can have exact same Protocol table but different Swap or not to swap 6 with 1 based om this

    /* The lines below are used to set the end points in microseconds (µs) if you have selected TX_CUSTOM.
     * A few things to considered:
     *  - If you put too big values compared to your TX you won't be able to reach the extremes which is bad for throttle as an example
     *  - If you put too low values you won't be able to use your full stick range, it will be maxed out before reaching the end
     *  - Centered stick value is usually 1500. It should match the middle between MIN and MAX, ie Center=(MAX-MIN)/2+MIN. If your TX is not centered you can adjust the value MIN or MAX.
     *  - 100% is the value when the model is by default, 125% is the value when you extend the servo travel which is only used by some protocols
     */
    #define PPM_MAX_100     1900  //      100%
    #define PPM_MIN_100     1100  //      100%
    #define PPM_MAX_125     2000  //      125%
    #define PPM_MIN_125     1000  //      125%

  #endif

  #ifdef AETR
    #undef AETR
  #endif

  #define TAER

  /* This to force the "Flash from TX" feature for all modules */
  #define CHECK_FOR_BOOTLOADER

  /* Since we have Multi Multi modules (nice wording right ;-)
   * which we need to share the same ID so we can use either to control
   * This to e.g. have two VLOS saftypilots in separate spots for the same aircraft
   * Be careful this is really if you want to be able to use one or
   *  another radio but not both at the same time in the same area!
   */
  #define FORCE_GLOBAL_ID   0x27244908

  /* Below needed in some cases, need more eval of crystal used before enabling... */
  //#define FORCE_FRSKYX_TUNING   0

  /* Below unlikely to be needed in our modules */
  //#define USE_CYRF6936_CH15_TUNING

  /* Not tested yet for xvert */
  //#define DSM_THROTTLE_KILL_CH 15

  /*
   * FAILSAFE behaviour is not wanted for autopiloted aircraft the AP
   * should detect real RX state from perspective if signal.
   * A failsave state is like still saying to AP;
   * the RX is OK we lost contact temporary which might but als this
   * temporary might also NOT be the case.
   * With Failsafe the is no guarantee about the timeframe, so not wanted...
   */

  #undef FAILSAFE_ENABLE

  /* Protocols using the CYRF6936 (DSM, Devo, Walkera...)are using the
   *  CYRF ID instead which should prevent duplicated IDs.
   *  But that is not what we want for VLOS flights with multiple TX's... so fixed ID it is.
   */
  #define FORCE_CYRF_ID "\x27\x24\x49\x08\x27\x24"

  /* If a module doesn't need the telemetry signal to be inverted
   * The Taranis X9D does it itself so no need for us also
   */
  //#undef INVERT_TELEMETRY

  /* We do it via bind button not a switch on TX, maybe we should... since we can ;) */
  #undef ENABLE_BIND_CH

  /* Since we also use this OpenTX project on some of our TX's,
   * ...we a really into open(source) things you know....
   */
  #undef MULTI_STATUS
  #define MULTI_TELEMETRY

  /* To still be able to use module in e.g. X9D we do set it, for the PPM TX's not needed but we have enought storage so leave it for more flexibility in swapping modules around*/
  //#undef ENABLE_SERIAL

  #ifdef TX_OPENUAS_MX22
    /* Limit the banks to easier switch, most used protocol are close on switch, 1 and 2... so not to rotate the switch back and forth to much */
    #undef NBR_BANKS

    /* redefine the number of banks to...eh... one only indeed */
    #define NBR_BANKS 1

      /* Use our own protocol table and their ordering */
    #define MY_PPM_PROT

    /* NOTE: JR/Graupner PPM Transmitter have CollectivePitch Throttle Swapped in output channel and in a Walkera pre-made heli firmware it cannot be changed... */
    /* for this the setting Chan order will be used with the JR/Graupner mask of 0x60000100 */

    /*
     * Only one (1) bank so we do nt need to be bothered with multipple button pressing in the field and watching a tiny blinking LED in full sunlight.
     * The rest of the obscure protocols we do not need anyhow.
     * The most used protocold at the top, is les rotation on the rotary switch.
     * If module is used in an serial enable TX, none of the knob fiddling is needed, this is for PPM TX only!
     *
     */


    /* The NBR_BANKS+1 Since the bug code not taking this cusom config into account:
     *  error: too many initializers for 'const PPM_Parameters [14]'
     * so there it is; added +1 for now. Basically Switch 0 is setting via serial...
     *
     */

    const PPM_Parameters My_PPM_prot[14*NBR_BANKS+1]={

    /* ******************************       BANK 1       ****************************** */
    /*  Switch pos     Protocol        Sub protocol          RX_Num             Power           Auto Bind           Option Chan Order */
    /*      1       */{PROTO_FRSKYX   ,EU_16           ,       0       ,       P_HIGH  ,       NO_AUTOBIND     , FRQ_TUNE ,       0x00000000 },      // option=fine freq tuning
    /*      2       */{PROTO_DSM      ,DSMX_11         ,       0       ,       P_HIGH  ,       NO_AUTOBIND     ,       12 ,       0x00000000 },      // option=number of channels
    /*      3       */{PROTO_Q303     ,CX10WD          ,       0       ,       P_HIGH  ,       NO_AUTOBIND     ,       0  ,       0x00000000 },
    /*      4       */{PROTO_DEVO     ,NONE            ,       0       ,       P_HIGH  ,       NO_AUTOBIND     ,       0  ,       0x60000100 },      // JR Heli channel ordering
    /*      5       */{PROTO_CFLIE    ,NONE            ,       0       ,       P_HIGH  ,       NO_AUTOBIND     ,       0  ,       0x00000000 },
    /*      6       */{PROTO_CX10     ,DM007           ,       0       ,       P_HIGH  ,       NO_AUTOBIND     ,       0  ,       0x00000000 },
    /*      7       */{PROTO_KN       ,WLTOYS          ,       0       ,       P_HIGH  ,       NO_AUTOBIND     ,       0  ,       0x00000000 },
    /*      8       */{PROTO_ESKY150  ,NONE            ,       0       ,       P_HIGH  ,       NO_AUTOBIND     ,       0  ,       0x00000000 },
    /*      9       */{PROTO_WK2x01   ,WK2801          ,       0       ,       P_HIGH  ,       NO_AUTOBIND     ,       0  ,       0x00000000 },
    /*      10      */{PROTO_V2X2     ,NONE            ,       0       ,       P_HIGH  ,       NO_AUTOBIND     ,       0  ,       0x00000000 },
    /*      11      */{PROTO_DSM      ,DSM2_22         ,       0       ,       P_HIGH  ,       NO_AUTOBIND     ,       8  ,       0x00000000 },      // option=number of channels
    /*      12      */{PROTO_DSM      ,DSMX_22         ,       0       ,       P_HIGH  ,       NO_AUTOBIND     ,       12 ,       0x00000000 },      // option=number of channels
    /*      13      */{PROTO_FRSKYX   ,CH_16           ,       0       ,       P_HIGH  ,       NO_AUTOBIND     , FRQ_TUNE ,       0x00000000 },      // option=fine freq tuning
    /*      14      */{PROTO_FLYSKY   ,Flysky          ,       0       ,       P_HIGH  ,       AUTOBIND        ,       0  ,       0x00000000 },
    };
  #endif

#endif
