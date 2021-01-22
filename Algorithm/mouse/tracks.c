#include"app_header.h"												/// Include custom created header file.

void GetMouseCoordinates(int *x,int *y)										/// Creates the Coordinates of Mouse Func.
														/// x Argument --> specified window
														/// y Argument --> specified window
{
    Display *d;													/// Display Func Variable.
    Window win;													/// root window the pointer is in */
    Window child;			    									/// For Child Creation.


    int rootx, rooty;												/// Variables for root window's origin.

    Atom atom_type_prop;											/// Describes the actual type of the property
    int actual_format;												/// Describes actual format of the property. 
    unsigned int mask;												/// Describes modifier keys and pointer buttons.

    unsigned long n_items, bytes_after_ret;									/// Bytes after return.

    Window *props;												/// Returns What type of data is present is return 
														/// Data can be char ,integer,short integer return as string format
    d = XOpenDisplay(NULL);											/// Open's The Display  ( XDisplay Manager ).

														/// XGetWindowProperty() --> obtain and change window properties
    XGetWindowProperty(d, DefaultRootWindow(d),									/// Load the Parameters.
	    XInternAtom(d, "_NET_ACTIVE_WINDOW", true),
	    0, 1, False, AnyPropertyType,
	    &atom_type_prop, &actual_format,
	    &n_items, &bytes_after_ret, (unsigned char**)&props);						

    XQueryPointer(d, props[0], &win,  &child,									/// XQueryPointer()  ---> get pointer coordinates
	    &rootx, &rooty, x, y, &mask);									/// Load the Parameters.

    XFree(props);												/// Free the What these Created.
    (void)XCloseDisplay(d);											/// Close the XDisplay Manager Display
}
