//
//  CRConnection.h
//  Criollo
//
//  Created by Cătălin Stan on 10/23/15.
//  Copyright © 2015 Cătălin Stan. All rights reserved.
//

#define CRConnectionSocketTagSendingResponse                        20

@class CRConnection, GCDAsyncSocket, CRServer, CRRequest, CRResponse;

@protocol CRConnectionDelegate <NSObject>

- (void)connection:(CRConnection*)connection didReceiveRequest:(CRRequest*)request response:(CRResponse*)response;

@end

@interface CRConnection : NSObject

@property (nonatomic, weak) id<CRConnectionDelegate> delegate;

@property (nonatomic, strong) GCDAsyncSocket* socket;
@property (nonatomic, weak) CRServer* server;

@property (nonatomic, strong) NSMutableArray<CRRequest*>* requests;

@property (nonatomic, strong) CRRequest* currentRequest;
@property (nonatomic, strong) NSDate* requestTime;

+ (NSData*)CRLFData;
+ (NSData*)CRLFCRLFData;

- (instancetype)initWithSocket:(GCDAsyncSocket*)socket server:(CRServer*)server NS_DESIGNATED_INITIALIZER;

- (CRResponse*)responseWithHTTPStatusCode:(NSUInteger)HTTPStatusCode;
- (CRResponse*)responseWithHTTPStatusCode:(NSUInteger)HTTPStatusCode description:(NSString *)description;
- (CRResponse*)responseWithHTTPStatusCode:(NSUInteger)HTTPStatusCode description:(NSString *)description version:(NSString *)version;

- (void)startReading;
- (void)didReceiveCompleteRequestHeaders;
- (void)didReceiveRequestBody;
- (void)didReceiveCompleteRequest;
- (void)sendData:(NSData*)data forResponse:(CRResponse*)response;
- (void)didFinishResponse:(CRResponse *)response;

@end
