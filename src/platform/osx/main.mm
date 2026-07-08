#include <AppKit/AppKit.h>
#import <Cocoa/Cocoa.h>
#include <chrono>

#include "core/CoreApp.hpp"

@interface AppDelegate : NSObject <NSApplicationDelegate>
@end

@interface SoftwareView : NSView
@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification*)notification {
	NSRect frame = NSMakeRect(100, 100, 800, 800);

	NSWindow* window = [[NSWindow alloc] initWithContentRect:frame
												   styleMask:(NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable)
													 backing:NSBackingStoreBuffered
													   defer:NO];

	[window setTitle:@"softrender"];
	[window center];
	[window makeKeyAndOrderFront:nil];
	[window setReleasedWhenClosed:NO];
	SoftwareView* view = [[SoftwareView alloc] initWithFrame:frame];
	[window setContentView: view];

	[NSApp activateIgnoringOtherApps:YES];
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)sender {
	return YES;
}

@end

@implementation SoftwareView
core::CoreApp* _app;
std::chrono::steady_clock::time_point _lastTime;

- (instancetype)initWithFrame:(NSRect)frame {
	self = [super initWithFrame:frame];

	if (self) {
		_app = new core::CoreApp();
		_lastTime = std::chrono::steady_clock::now();

		[NSTimer scheduledTimerWithTimeInterval:1.0 / 60.0 target:self selector:@selector(redraw) userInfo:nil repeats:YES];
	}

	return self;
}

- (void)dealloc {
	[super dealloc];
	delete _app;
}

- (void)redraw {
	auto now = std::chrono::steady_clock::now();
	float dt = std::chrono::duration<float>(now - _lastTime).count();
	_lastTime = now;
	_app->update(dt);
	[self setNeedsDisplay:YES];
}

- (void)drawRect:(NSRect)dirtyRect {
	const uint32_t* pixels = _app->getFramebuffer();

	CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();

	CGContextRef ctx = [[NSGraphicsContext currentContext] CGContext];

	CGDataProviderRef provider = CGDataProviderCreateWithData(nullptr, pixels, _app->getWidth() * _app->getHeight() * 4, nullptr);

	CGImageRef image = CGImageCreate(_app->getWidth(), _app->getHeight(), 8, 32, _app->getWidth() * 4, colorSpace, kCGImageAlphaPremultipliedFirst | kCGBitmapByteOrder32Little, provider, nullptr,
		false, kCGRenderingIntentDefault);

	CGContextDrawImage(ctx, CGRectMake(0, 0, _app->getWidth(), _app->getHeight()), image);

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
