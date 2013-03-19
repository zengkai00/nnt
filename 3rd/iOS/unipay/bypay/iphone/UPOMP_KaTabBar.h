//
//  KaTabBar.h
//  Paperpay
//
//  Created by pei xunjun on 11-7-18.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "UPOMP_KaTabItem.h"

@protocol UPOMP_KaTabBarDelegate;
@interface UPOMP_KaTabBar : UIView {
	//回调函数
	id <UPOMP_KaTabBarDelegate> delegate;
	//背景图片
	UIImageView *backgroudImage;
	//元素数组
	NSArray *itemArray;
	//选中元素的 index
	int selectedIndex;
}
//初始方法
- (id)initWithFrame:(CGRect)frame items:(NSArray*)items;
//设置背景图片
- (void)setBackgroundImage:(UIImage*)image;
//设置选中元素
- (void)setSelectedItem:(int)index;
@property (nonatomic, assign) id <UPOMP_KaTabBarDelegate> delegate;
@property int selectedIndex;
@end

@protocol UPOMP_KaTabBarDelegate<NSObject>
@required
-(void)tabBarSelectedIndexChange:(int)index;
@end