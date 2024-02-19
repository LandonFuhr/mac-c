#include <Carbon/Carbon.h>
#include <objc/objc-runtime.h>

// We need to tell the compiler the exact arguments for objc_msgSend. If
// we use a variadic function it will not work properly.
#define objc_msgSend_Class_SEL ((id(*)(Class, SEL))objc_msgSend)
#define objc_msgSend_Class_SEL_id ((id(*)(Class, SEL, id))objc_msgSend)
#define objc_msgSend_Class_SEL_int ((id(*)(Class, SEL, int))objc_msgSend)
#define objc_msgSend_Class_SEL_str ((id(*)(Class, SEL, char *))objc_msgSend)
#define objc_msgSend_id_SEL ((id(*)(id, SEL))objc_msgSend)
#define objc_msgSend_id_SEL_CGRect_int_int_int                                 \
  ((id(*)(id, SEL, struct CGRect, int, int, int))objc_msgSend)
#define objc_msgSend_id_SEL_id ((id(*)(id, SEL, id))objc_msgSend)
#define objc_msgSend_id_SEL_id_SEL_id                                          \
  ((id(*)(id, SEL, id, SEL, id))objc_msgSend)
#define objc_msgSend_id_SEL_int ((id(*)(id, SEL, int))objc_msgSend)
#define objc_msgSend_id_SEL_ptr ((id(*)(id, SEL, void *))objc_msgSend)

int main(void) {
  // app
  id NSApp;
  {
    // In Objective-C, the `NSApp` global variable is automatically set when
    // calling [NSApplication sharedApplication]
    //
    // We have to set this manually because we don't have the Objective-C magic.
    //
    // The naming is confusing because it's capitalized like a Class but it's
    // not actually a Class.
    //
    // https://developer.apple.com/documentation/appkit/nsapp?language=objc
    //
    // NSApp = [NSApplication sharedApplication]
    NSApp = objc_msgSend_Class_SEL(objc_getClass("NSApplication"),
                                   sel_getUid("sharedApplication"));
    // [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular]
    objc_msgSend_id_SEL_int(NSApp, sel_getUid("setActivationPolicy:"),
                            0 /* NSApplicationActivationPolicyRegular */);
    // [NSApp activateIgnoringOtherApps:true]
    objc_msgSend_id_SEL_int(NSApp, sel_getUid("activateIgnoringOtherApps:"),
                            true);
  }

  // menu bar
  {
    // id menubar = [NSMenu new]
    id menubar =
        objc_msgSend_Class_SEL(objc_getClass("NSMenu"), sel_getUid("new"));
    // [NSApp setMainMenu:menubar]
    objc_msgSend_id_SEL_id(NSApp, sel_getUid("setMainMenu:"), menubar);

    // app menu
    {
      // id appMenuItem = [NSMenuItem new]
      id appMenuItem = objc_msgSend_Class_SEL(objc_getClass("NSMenuItem"),
                                              sel_getUid("new"));
      // [menubar addItem:appMenuItem]
      objc_msgSend_id_SEL_id(menubar, sel_getUid("addItem:"), appMenuItem);
      // id appMenu = [NSMenu new]
      id appMenu =
          objc_msgSend_Class_SEL(objc_getClass("NSMenu"), sel_getUid("new"));
      // [appMenuItem setSubmenu:appMenu]
      objc_msgSend_id_SEL_id(appMenuItem, sel_getUid("setSubmenu:"), appMenu);

      // Quit
      {
        // [appMenu
        //  addItemWithTitle:@"Quit"
        //  action:@selector(terminate:)
        //  keyEquivalent:@"q"
        // ]
        objc_msgSend_id_SEL_id_SEL_id(
            appMenu, sel_getUid("addItemWithTitle:action:keyEquivalent:"),
            objc_msgSend_Class_SEL_str(objc_getClass("NSString"),
                                       sel_getUid("stringWithUTF8String:"),
                                       "Quit"),
            sel_getUid("terminate:"),
            objc_msgSend_Class_SEL_str(objc_getClass("NSString"),
                                       sel_getUid("stringWithUTF8String:"),
                                       "q"));
      }
    }
  }

  // window
  {
    struct CGRect frameRect = {{0, 0}, {600, 500}};
    // id window =  [[NSWindow alloc]
    //  initWithContentRect:frameRect
    //  styleMask:NSWindowStyleMaskTitled|NSWindowStyleMaskClosable|NSWindowStyleMaskMiniaturizable|NSWindowStyleMaskResizable|NSWindowStyleMaskFullSizeContentView
    //  backing:NSBackingStoreBuffered
    //  defer:false
    // ]
    id window = objc_msgSend_id_SEL_CGRect_int_int_int(
        objc_msgSend_Class_SEL(objc_getClass("NSWindow"), sel_getUid("alloc")),
        sel_getUid("initWithContentRect:styleMask:backing:defer:"),
        frameRect, // initWithContentRect
        (1 << 0) /* NSWindowStyleMaskTitled */ |
            (1 << 1) /* NSWindowStyleMaskClosable */ |
            (1 << 2) /* NSWindowStyleMaskMiniaturizable */ |
            (1 << 3) /* NSWindowStyleMaskResizable */ |
            (1 << 15) /* NSWindowStyleMaskFullSizeContentView */, // styleMask
        2 /* NSBackingStoreBuffered */,                           // backing
        false                                                     // defer
    );
    // [window makeKeyAndOrderFront:nil]
    objc_msgSend_id_SEL_ptr(window, sel_getUid("makeKeyAndOrderFront:"), nil);
    // [window setTitlebarAppearsTransparent:true]
    objc_msgSend_id_SEL_int(window,
                            sel_getUid("setTitlebarAppearsTransparent:"), true);
  }

  // [NSApp run]
  objc_msgSend_id_SEL(NSApp, sel_getUid("run"));

  return 0;
}
