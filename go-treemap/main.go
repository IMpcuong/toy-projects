package main

/*
#cgo CFLAGS: -x objective-c
#cgo LDFLAGS: -framework Cocoa -framework Foundation
#import <Foundation/Foundation.h>

long long getFileSize(const char* path) {
  NSString *nsPath = [NSString stringWithUTF8String:path];
  NSFileManager *fileManager = [NSFileManager defaultManager];
  NSError *error = nil;
  NSDictionary *attributes = [fileManager attributesOfItemAtPath:nsPath error:&error];

  if (error) {
  	NSLog(@"Error getting file attributes: %@", error);
  	return -1;
	}

	return [attributes fileSize];
}

char* getFileCreationDate(const char* path) {
	NSString *nsPath = [NSString stringWithUTF8String:path];
	NSFileManager *fileManager = [NSFileManager defaultManager];
	NSError *error = nil;
	NSDictionary *attributes = [fileManager attributesOfItemAtPath:nsPath error:&error];

	if (error) {
		NSLog(@"Error getting file attributes: %@", error);
		return NULL;
	}

	NSDate *creationDate = [attributes fileCreationDate];
	NSDateFormatter *formatter = [[NSDateFormatter alloc] init];
	[formatter setDateFormat:@"yyyy-MM-dd HH:mm:ss"];
	NSString *dateString = [formatter stringFromDate:creationDate];

	const char *cString = [dateString UTF8String];
	char *result = (char*) malloc(strlen(cString) + 1);
	strcpy(result, cString);
	return result;
}
*/
import "C"
import (
	"fmt"
	"unsafe"
)

func getFileSize(path string) int64 {
	cPath := C.CString(path)
	defer C.free(unsafe.Pointer(cPath))
	return int64(C.getFileSize(cPath))
}

func getFileCreationDate(path string) string {
	cPath := C.CString(path)
	defer C.free(unsafe.Pointer(cPath))
	cDate := C.getFileCreationDate(cPath)
	defer C.free(unsafe.Pointer(cDate))
	return C.GoString(cDate)
}

func main() {
	filePath := "./main.go"

	size := getFileSize(filePath)
	if size >= 0 {
		fmt.Printf("File size: %d bytes\n", size)
	} else {
		fmt.Println("Error getting file size")
	}

	creationDate := getFileCreationDate(filePath)
	if creationDate != "" {
		fmt.Printf("File creation date: %s\n", creationDate)
	} else {
		fmt.Println("Error getting file creation date")
	}
}
