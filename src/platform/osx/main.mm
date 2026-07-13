#include <AppKit/AppKit.h>
#import <Cocoa/Cocoa.h>

#include <cstddef>

#include "core/CoreApp.hpp"
#include "render/Framebuffer.hpp"

@interface AppDelegate : NSObject <NSApplicationDelegate>
@end

@interface SoftwareView : NSView
@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification*)notification {
	NSRect frame = NSMakeRect(100, 100, 1366, 768);

	NSWindow* window = [[NSWindow alloc] initWithContentRect:frame
												   styleMask:(NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable)
													 backing:NSBackingStoreBuffered
													   defer:NO];

	[window setTitle:@"softrender"];
	[window center];
	[window makeKeyAndOrderFront:nil];
	[window setReleasedWhenClosed:NO];
	SoftwareView* view = [[SoftwareView alloc] initWithFrame:frame];
	[window setContentView:view];

	[NSApp activateIgnoringOtherApps:YES];
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)sender {
	return YES;
}

@end

@implementation SoftwareView
core::CoreApp* _app;

- (instancetype)initWithFrame:(NSRect)frame {
	self = [super initWithFrame:frame];

	if (self) {
		_app = new core::CoreApp(400, 225);
		NSTimer* timer = [NSTimer scheduledTimerWithTimeInterval:1.0 / 60.0
			target:self
			selector:@selector(redraw)
			userInfo:nil
			repeats:YES
		];
		[[NSRunLoop mainRunLoop] addTimer:timer forMode:NSRunLoopCommonModes];
	}

	return self;
}

- (void)dealloc {
	[super dealloc];
	delete _app;
}

- (void)redraw {
	_app->update();
	[self setNeedsDisplay:YES];
}

- (void)drawRect:(NSRect)dirtyRect {
	render::Framebuffer* framebuffer = render::Framebuffer::instance();

	const uint32_t* pixels = framebuffer->getPixels();

	CGContextRef ctx = [[NSGraphicsContext currentContext] CGContext];

	CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();

	size_t pixelsSize = framebuffer->width() * framebuffer->height() * 4;

	CGDataProviderRef provider = CGDataProviderCreateWithData(
		nullptr,
		pixels,
		pixelsSize,
		nullptr
	);

	CGImageRef image = CGImageCreate(
		framebuffer->width(),
		framebuffer->height(),
		8,
		32,
		framebuffer->width() * 4,
		colorSpace,
		kCGImageAlphaPremultipliedFirst | kCGBitmapByteOrder32Little,
		provider,
		nullptr,
		false,
		kCGRenderingIntentDefault
	);


	NSRect bounds = [self bounds];

	float scaleX = bounds.size.width / _app->getWidth();
	float scaleY = bounds.size.height / _app->getHeight();

	float scale = MIN(scaleX, scaleY);

	float width = _app->getWidth() * scale;
	float height = _app->getHeight() * scale;

	float x = (bounds.size.width - width) * 0.5f;
	float y = (bounds.size.height - height) * 0.5f;

	CGContextDrawImage(
		ctx,
		CGRectMake(x, y, width, height),
		image
	);


	CGImageRelease(image);
	CGDataProviderRelease(provider);
	CGColorSpaceRelease(colorSpace);
}

@end

int main(int argc, char** argv) {
	@autoreleasepool {
		NSApplication* app = [NSApplication sharedApplication];

		[app setActivationPolicy:NSApplicationActivationPolicyRegular];

		AppDelegate* delegate = [[AppDelegate alloc] init];
		[app setDelegate:delegate];

		NSMenu* menubar = [[NSMenu alloc] init];
		NSMenuItem* appMenuItem = [[NSMenuItem alloc] init];
		[menubar addItem:appMenuItem];
		[NSApp setMainMenu:menubar];

		NSMenu* appMenu = [[NSMenu alloc] init];

		NSString* quitTitle = [@"Quit " stringByAppendingString:[[NSProcessInfo processInfo] processName]];
		NSMenuItem* quitItem = [[NSMenuItem alloc] initWithTitle:quitTitle action:@selector(terminate:) keyEquivalent:@"q"];

		[appMenu addItem:quitItem];
		[appMenuItem setSubmenu:appMenu];
		[app run];
	}

	return 0;
}
